import argparse
import os
import re
import subprocess

MATCH_DECLARATION = re.compile(
    r"__GENERATE_API \$ __GEN_ID_(?P<id>\w+) \$ (?P<type>\w+(?:\*+|\s+))(?P<name>.+?)\((?P<args>.*?)\) \$",
    re.DOTALL | re.MULTILINE,
)

MATCH_ARGS = re.compile(r"(?P<type>\w+(?:\*+|\s+))(?P<name>\w+),")


def sizeof(args):
    """Return a string that describes the size of a list of arguments."""
    return " + ".join(a["sizeof"] for a in args) if args != [] else "0"


def parse_declarations(source):
    """Parse all declarations in the given source."""
    declarations = []
    for decl in MATCH_DECLARATION.finditer(source):
        id = decl.group("id")
        return_type = decl.group("type").strip()
        name = decl.group("name")
        args = []
        args_str = decl.group("args")

        # Parse arguments
        for arg in MATCH_ARGS.finditer(args_str + ","):
            arg_type = arg.group("type").strip()
            arg_name = arg.group("name")

            args.append({
                "type": arg_type,
                "name": arg_name,
                "sizeof": "sizeof({})".format(arg_type),
                "offset": sizeof(args),
            })

        declarations.append({
            "id": id,
            "return_type": return_type,
            "name": name,
            "args": args,
            "args_str": args_str,
        })

    return declarations


def main():
    parser = argparse.ArgumentParser(
        description="Generate the API stubs from a header file."
    )
    parser.add_argument(
        "-H", "--header", required=True, help="The header to base the definitions on."
    )
    parser.add_argument(
        "-c", "--client", required=True, help="The output client-side c source file."
    )
    parser.add_argument(
        "-s", "--server", required=True, help="The output server-side c source file."
    )
    args = parser.parse_args()

    # Run the preprocessor on the header file to get the API definitions.
    #
    # For this, we first need a source to include the header which contains
    # an alternative definition of the `API` macro that marks definitions in
    # a way we can find later on.
    api_src = """\
#define API(id, def) __GENERATE_API $ __GEN_ID_##id $ def $
#include "{header}"
""".format(
        header=os.path.relpath(args.header)
    )

    # Evaluate the preprocessor
    source = subprocess.check_output(
        ["gcc", "-E", "-"], input=api_src.encode()
    ).decode()

    declarations = parse_declarations(source)
    fmt_header = {
        "header": os.path.basename(args.header)
    }

    # Generate Client {{{
    with open(args.client, "w") as f_client:
        tmp = """\
#include <stdio.h>

#include "{header}"
#include "api/caller.h"
"""
        f_client.write(tmp.format(**fmt_header))

        for decl in declarations:
            decl["total_size"] = sizeof(decl["args"])
            tmp = """\

/* Autogenerated stub for {id} */
{return_type} {name}({args_str})
{{
        const int size = {total_size};
        void*buffer;

        buffer = _api_call_start({id}, size);
        /* TODO: Check if buffer is not NULL */

"""
            f_client.write(tmp.format(**decl))

            for i, arg in enumerate(decl["args"]):
                tmp = """\
        *({type}*)(buffer + {offset}) = {name};
"""
                f_client.write(tmp.format(**arg))

            if decl["return_type"] == "void":
                # Don't return if return type is void
                tmp = """\

        _api_call_transact(buffer);
}}
"""
                f_client.write(tmp.format(**decl))
            else:
                tmp = """\

        return *({return_type}*)_api_call_transact(buffer);
}}
"""
                f_client.write(tmp.format(**decl))
    # END: Generate Client }}}

    # Generate Dispatcher {{{
    with open(args.server, "w") as f_dispatcher:
        tmp = """\
#include <stdio.h>
#include "{header}"

void __api_dispatch_call(uint32_t id, void*buffer)
{{
        switch (id) {{
"""
        f_dispatcher.write(tmp.format(**fmt_header))

        for decl in declarations:
            if decl["return_type"] == "void":
                tmp = """\
        case {id}:
                {name}("""
                f_dispatcher.write(tmp.format(**decl))
            else:
                tmp = """\
        case {id}:
                *(({return_type}*)buffer) = {name}("""
                f_dispatcher.write(tmp.format(**decl))

            for i, arg in enumerate(decl["args"]):
                arg["comma"] = "" if i == 0 else ","
                tmp = """{comma}
                        *({type}*)(buffer + {offset})"""
                f_dispatcher.write(tmp.format(**arg))

            tmp = """
                );
                break;
"""
            f_dispatcher.write(tmp.format(**decl))

        tmp = """\
        default:
                /* TODO: Better error handling */
                printf("Error: API function %x is unknown!!\\n", id);
                break;
        }}
}}
"""
        f_dispatcher.write(tmp.format(**fmt_header))
    # END: Generate Dispatcher }}}


if __name__ == "__main__":
    main()
