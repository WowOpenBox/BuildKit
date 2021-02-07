# BuildKit
Dependencies to build WOB/OBM binaries, ie a single binary with Tcl/Tk+TWAPI+misc dependencies


Note that the license of each component is their own

Source of info and data:

http://kitcreator.rkeene.org/fossil/home

Need to pick MetaKit or you get a vfs error later
Need the runtime to be threaded

For the runtime: (runtime.exe)

URL: http://kitcreator.rkeene.org/kits/building/7dd39658b1f9a7ebf35ca10ca66f0a5630e049dc/
Description: Tcl 8.6.10, KitCreator 0.12.0, Platform win64, Threaded, Packages: mk4tcl, tk

For build time: same without Tk: (tclkit/tclkit.exe)
URL: http://kitcreator.rkeene.org/kits/8ab68b842c29538075259d620218331cae45e995/
Description: Tcl 8.6.10, KitCreator 0.12.0, Platform win64, Without Tcl pkgs/ and all encodings, Unthreaded, Packages: mk4tcl

https://www.magicsplat.com/blog/starpack-example/

twapi bin https://sourceforge.net/projects/twapi/files/Current%20Releases/Tcl%20Windows%20API/twapi-4.5.2/twapi-bin-4.5.2.zip/download

sdx kit : https://chiselapp.com/user/aspect/repository/sdx/uv/sdx-20110317.kit

tooltip is from tklib https://core.tcl-lang.org/tklib/wiki?name=Releases

tkdnd is from https://github.com/petasis/tkdnd/releases


Manually added our ico to runtime.exe as sdx seems unable to otherwise replace them all


upx is from https://github.com/upx/upx/releases/tag/v3.96


rrenable is a small program to start OpenMultiBoxing.exe as a child program in debug mode (which allows that child to set window focus)
