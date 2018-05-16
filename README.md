NeilOS Pi - A terrible, homebrew, Raspberry Pi 3 Operating System
=================================================================

Whilst searching for some projects to do that were still programming, but not
specifically game related, I decided to grab myself a Rapsberry Pi 3, and start
writing my own OS for it. No hard goals, but what I'm intending to get going,
in no specific order:
- Hook up some hardware for basic I/O (PC speaker, some GPI/GPO for debugging)
- Ability to load over serial to avoid swapping the MicroSD so much.
- Multitasking kernel, taking advantage of the 4-cores.
- Audio I/O, probably by strapping some better DAC/ADCs to it.
- 3D Graphics. Not sure if that'd be exposed via a standard API (GL, VK, etc), or something custom.

I'd like to say a thanks to a handful of folks for being public about their RPi work online,
and the tutorials/blogs they write on the subject. It's made getting setup and running much
easier, and a good source for inspiration:
- Jaymin Kessler - http://maisonikkoku.com/jaystation2/blog_main.html
- Zoltan Baldaszti - https://github.com/bztsrc/raspi3-tutorial
- Peter Lemon - https://github.com/PeterLemon/RaspberryPi
- Leon de Boer - https://github.com/LdB-ECM/Raspberry-Pi
- David Welch - https://github.com/dwelch67/raspberrypi
