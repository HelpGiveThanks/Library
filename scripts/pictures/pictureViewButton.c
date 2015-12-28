pictures: pictureViewButton
#
#
#Toggle between small and full screen picture window.
Go to Field [ ]
Move/Resize Window [ Current Window; Height: If ( Get (ScreenHeight) / 2 = Get (WindowHeight) ; Get (ScreenHeight) ; Get
(ScreenHeight) / 2 ); Width: If ( Get (ScreenWidth) / 2 = Get (WindowWidth) ; Get (ScreenWidth) ; Get (ScreenWidth) / 2 ); Top: If
( Get (ScreenHeight) / 2 = Get (WindowHeight) ; 0 ; Get (ScreenHeight) / 4 ); Left: If ( Get (ScreenWidth) / 2 = Get
(WindowWidth) ; 0 ; Get (ScreenWidth) / 4 ) ]
#
#Had to insert two zoom levels in order to get
#the header to show up. With the just the 100
#zoom, the header will sometimes disappear,
#until you manually zoom 75 then back to 100.
Set Zoom Level
[ 75% ]
Set Zoom Level
[ 100% ]
December 27, ଘ౮27 19:47:33 Library.fp7 - pictureViewButton -1-
