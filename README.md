# Fork of card10 badge firmware


This is a fork of the Firmware for the card10 badge for the Chaos Communication Camp 2019. Find the official repo on GitLab:
https://git.card10.badge.events.ccc.de/card10/firmware

## This repo

Custom module called displaybuffer adds some high-performing bling:

```
import displaybuffer
disp = displaybuffer.open()

counter = 0

while 1:
  res = disp.rainbowbuff(counter)
  res = disp.wrencher()
  res = disp.showbuff()
  counter += 1
  if counter > 71:
    counter = 0
```

