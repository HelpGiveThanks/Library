July 20, 2018 21:32:23 Library.fmp12 - pictureViewButton -1-
pictures: pictureViewButton
#
#
#Toggle between small and full screen picture
#window, unless on iDevice, in which case tell
#the user how to use two fingers to zoom
#in and out.
Go to Field [ ]
If [ Get ( SystemPlatform ) = 3 ]
Show Custom Dialog [ Message: "Touch two fingers to the screen and pinch and spread apart to zoom in and out. NOTE: On
desktop/laptop computers this button increases/decreases the media's size."; Default Button: “OK”, Commit: “Yes” ]
Else
If [ TEMP::InventoryLibraryYN ≠ "" ]
Move/Resize Window [ Current Window; Height: If ( 435 = Get (WindowHeight) ; Get (ScreenHeight) ; 435 ); Width: If ( 435
= Get (WindowHeight); Get (ScreenWidth) ; 400 ); Top: If ( 435 = Get (WindowHeight) ; 0 ; Get (ScreenHeight) / 4 );
Left: If ( 435 = Get (WindowHeight) ; 0 ; Get (ScreenWidth) / 4 ) ]
Else
Move/Resize Window [ Current Window; Height: If ( 395 = Get (WindowHeight) ; Get (ScreenHeight) ; 395 ); Width: If ( 395
= Get (WindowHeight); Get (ScreenWidth) ; 400 ); Top: If ( 395 = Get (WindowHeight) ; 0 ; Get (ScreenHeight) / 4 );
Left: If ( 395= Get (WindowHeight) ; 0 ; Get (ScreenWidth) / 4 ) ]
End If
End If
#
#
#Turned this off because it kept YouTube
#video's from resizing quickly.
// #Had to insert two zoom levels in order to get
// #the header to show up. With the just the 100
// #zoom, the header will sometimes disappear,
// #until you manually zoom 75 then back to 100.
// Set Zoom Level [ 75%; Camera: Back; Resolution: Full ]
// Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
