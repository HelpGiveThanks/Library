October 8, 2018 14:58:50 Library.fmp12 - -1-
gotoOtherLibrarySelectWindows
librarySetup: gotoOtherLibrarySelectWindows
#
#Determine the names of all the windows
#open for this library.
Set Variable [ $windows; Value:WindowNames(MemorySwitch::currentLibraryName) ]
#
#If there is only one window open, then
#restart this library.
If [ GetValue ( $windows ; 2 ) = "" ]
Perform Script [ “restartDatabase” ]
Exit Script [ ]
End If
#
#If there are only two windows open, and
#none of them are named report, then
#resize them equally and move them
#next to each other.
If [ GetValue ( $windows ; 3 ) = "" and
LeftWords (FilterValues ( WindowNames(Get(FileName)) ; "Report" ) ; 1 ) ≠ "Report" ]
#
#First, resize and move the Tag Menus
#window right.
Move/Resize Window [ Name: "Tag Menus"; Current file; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0;
Left: Get ( ScreenWidth ) / 2 ]
#
#Figure out the name of the main window
#and resize and move it to the left.
If [ GetValue ( $windows ; 1 ) ≠ "Tag Menus" ]
Move/Resize Window [ Name: GetValue ( $windows ; 1 ); Current file; Height: Get ( ScreenHeight ); Width: Get
( ScreenWidth ) / 2; Top: 0; Left: 0 ]
Select Window [ Name: GetValue ( $windows ; 1 ); Current file ]
Else If [ GetValue ( $windows ; 2 ) ≠ "Tag Menus" ]
Move/Resize Window [ Name: GetValue ( $windows ; 2 ); Current file; Height: Get ( ScreenHeight ); Width: Get
( ScreenWidth ) / 2; Top: 0; Left: 0 ]
Select Window [ Name: GetValue ( $windows ; 2 ); Current file ]
End If
End If
#
#If there are only two windows open, and
#one of them is named report, then resize
#them as follows:
If [ GetValue ( $windows ; 3 ) = "" and
LeftWords (FilterValues ( WindowNames(Get(FileName)) ; "Report" ) ; 1 ) = "Report" ]
#
#The size of the Tag Menus window in the Report
#section can be larger than half the window width.
Move/Resize Window [ Name: "Tag Menus"; Current file; Height: Get ( ScreenHeight ); Width: Get (ScreenWidth) - 594; Top: 0;
Left: 594 ]
#
Select Window [ Name: "Report"; Current file ]
Move/Resize Window [ Name: "Report"; Current file; Height: Get ( ScreenHeight ); Width: 594; Top: 0; Left: 0 ]
End If
#
#If there are three windows open, and
#one of them is named report, then resize
#them as follows:
If [ GetValue ( $windows ; 3 ) ≠ "" and
LeftWords (FilterValues ( WindowNames(Get(FileName)) ; "Report" ) ; 1 ) = "Report" ]
Move/Resize Window [ Name: "Reference"; Current file; Height: Get ( ScreenHeight ); Width: 290; Top: 0; Left: Get
( ScreenWidth ) - 290 ]
#
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get ( ScreenWidth ) - 884 < 334 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Height: Get ( ScreenHeight ); Width: 334; Top: 0; Left: 594 ]
Else
Move/Resize Window [ Name: "Tag Menus"; Current file; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) - 884;
Top: 0; Left: 594 ]
End If
#
Select Window [ Name: "Report"; Current file ]
Move/Resize Window [ Name: "Report"; Current file; Height: Get ( ScreenHeight ); Width: 594; Top: 0; Left: 0 ]
End If
#
#If there are three windows open, and
#one of them is named test, then resize
#them as follows:
If [ GetValue ( $windows ; 3 ) ≠ "" and
LeftWords (FilterValues ( WindowNames(Get(FileName)) ; "Test" ) ; 1 ) = "Test" ]
#The size of the Tag Menus window in the Report
#section can be larger than half the window width.
Move/Resize Window [ Name: "Reference"; Current file; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 3; Top: 0;
Left: ( Get ( ScreenWidth ) / 3 ) * 2 ]
#
Move/Resize Window [ Name: "Tag Menus"; Current file; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 3; Top: 0;
Left: Get ( ScreenWidth ) / 3 ]
#
Select Window [ Name: "Test"; Current file ]
Move/Resize Window [ Name: "Test"; Current file; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 3; Top: 0; Left: 0 ]
End If
#
#Clear the $$path variable.
Set Variable [ $$path ]
#
#
