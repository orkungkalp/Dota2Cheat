# Dota2Cheat: now with ImGui!
SDK folder code is from another github repo, McDota by LWSS. It's a very helpful source regarding memory structures

Also using GLFW, GLEW and ImGui for the interface, cheers to their wonderful creators!
## Building
Open the project in Visual Studio and build as **Release x64**
## Injecting
I recommend using [Extreme Injector v3.7.2](https://www.unknowncheats.me/forum/downloads.php?do=file&id=21570) with either Thread Hijacking or the default option

# Features
To open the cheat menu, press Insert

This list is subject to frequent change as I'm testing new features
* Illusion coloring(red for enemy's, green for friendly)
* Automation:
  * Magic Wand and Faerie Fire usage with customizable health tresholds
  * Hand of Midas usage on nearby big neutrals, ranged & flagbearer lane creeps and catapults
  * Bounty rune pickup
  * Tome of Knowledge purchase
  * Redirects spell casts from illusions to the real hero
  
* Information:
  * Visible by Enemy — currently shows a Skyrim inspired HIDDEN/DETECTED text on screen

* Convars:
  * `sv_cheats` spoofing
  * custom `dota_camera_distance` with proper `r_farz` and `fog_enable`(no clipping or blue fog)
  * `dota_use_particle_fow` — shows more particles in FoW, including the teleportation effects
  
I intend to implement most of the usual cheat functionality
