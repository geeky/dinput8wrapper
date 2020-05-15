# dinput8wrapper
This is a DirectInput 8 (dinput8.dll) Wrapper, which internally uses Raw-Input instead of DirectInput.

Initially created to have a different way to fix the frame stuttering caused by regular EnumDevices()-calls in "Kane & Lynch: Dead Men"

Other workarounds are listed here: https://www.pcgamingwiki.com/wiki/Kane_%26_Lynch:_Dead_Men#Stuttering

## Current state:
* Mostly untested, may cause crashes
* Only supports Keyboard and Mouse, but no gamepads
* Does only implement a small subset of the DirectInput8-Interfaces 
* Feel free to fork / Send Pull-Requests

## How to use
* Get the latest version here: https://github.com/geeky/dinput8wrapper/releases
* Copy the dinput8.dll to the folder where your game has its main executable and hope that the game will load it ;D
