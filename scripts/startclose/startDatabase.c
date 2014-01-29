startclose: startDatabase
#
#Check if database is being started by new library script.
Set Window Title [ Current Window; New Title: "Library Update" ]
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
If [ backup::newLibrary = "234874920347574weidf792342f9823984" ]
Show Custom Dialog [ Message: "Are you sure you want to delete the data in " & TEMP::ﬁleName & " to make it a new empty one? If you are not sure, DO NOT CLICK any of the buttons. Instead, check the folder where this library is located and make sure this is a copy of the orignal and
not the original. Next click either the stop or proceed button."; Buttons: “stop”, “proceed” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Exit Script [ ]
End If
Go to Layout [ “backup” (backup) ]
Perform Script [ “createEmptyLibrary” ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Exit Script [ ]
End If
#
If [ backup::newLibrary = "newLibrary" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Show Custom Dialog [ Message: "1) Create a new, empty library." & ¶ & "
2) Import another library's records into version " & tempSetup::verionNumber & " of the library application."; Buttons: “new”, “import”, “cancel” ]
If [ Get ( LastMessageChoice ) = 3 ]
Close Window [ Current Window ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $$OldNodeID; Value:tempSetup::kdefaultNodePrimary ]
If [ $$OldNodeID = "" ]
Set Variable [ $$OldNodeID; Value:1 ]
End If
Go to Layout [ “backup” (backup) ]
Perform Script [ “createEmptyLibrary” ]
Set Field [ backup::newLibrary; "" ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Show Custom Dialog [ Message: "On some imports FileMaker crashes. Cancel this import and duplicate this LibraryNEW ﬁle if you do not have an extra in case this happens. If it does happen, delete the updated library, and try again."; Buttons: “OK”, “cancel” ]
If [ Get ( LastMessageChoice ) = 2 ]
Close Window [ Current Window ]
Exit Script [ ]
End If
Perform Script [ “update” ]
Perform Script [ “startDatabase” ]
Exit Script [ ]
End If
End If
#
#Check if database is being started by update script.
Paste [ backup::backup ]
[ Select ]
If [ backup::backup = "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" ]
Set Field [ backup::backup; "" ]
Copy [ backup::ﬁlepath ]
[ Select ]
Close Window [ Name: "Tag Menus"; Current ﬁle ]
Close Window [ Current Window ]
End If
#
Go to Layout [ “defaultSetup” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Set Window Title [ Current Window; New Title: "Setup" ]
If [ Get ( SystemPlatform ) = - 2 ]
// New Window [ Name: "Day"; Height: Get (WindowDesktopHeight) - 21; Width: 344; Top: 0; Left: Get (ScreenWidth) - 688 ]
Move/Resize Window [ Current Window; Height: Get (WindowDesktopHeight) - 21; Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Else
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
End If
Go to Field [ ]
#
#goto Tag Menus window
If [ Get ( SystemPlatform ) = - 2 ]
New Window [ Name: "Tag Menus"; Height: Get (WindowDesktopHeight) - 21; Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2 ]
Else
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2 ]
End If
Go to Layout [ “defaultHealth” (tagMenus) ]
#
#
#
#Show regular menus if Admin logs in only.
Show/Hide Text Ruler
[ Hide ]
If [ Get ( AccountName ) = "Admin" ]
Show/Hide Status Area
[ Hide ]
Else
Show/Hide Status Area
[ Lock; Hide ]
End If
#
#
Perform Script [ “defaultSectionMenu” ]
Perform Script [ “setDefaultSection” ]
Select Window [ Name: "Setup"; Current ﬁle ]
#
Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
Show All Records
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ Get ( FilePath ) = MemorySwitch::<Field Missing> ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ Get ( FilePath ) ≠ MemorySwitch::<Field Missing> ]
New Record/Request
Set Field [ MemorySwitch::<File Missing>; TEMP::ﬁlePath ]
Set Field [ MemorySwitch::<File Missing>; TEMP::ﬁleName ]
End If
Set Field [ MemorySwitch::<File Missing>; Get ( FilePath ) ]
#
#Report version number to Memory Switch Table.
Set Field [ MemorySwitch::<File Missing>; tempSetup::verionNumber ]
#
Go to Layout [ “defaultSetup” (tempSetup) ]
January 28, 平成26 17:32:13 Empty Library.fp7 - startDatabase -1-startclose: startDatabase
Go to Layout [ “defaultSetup” (tempSetup) ]
#
#Show regular menus if Admin logs in only.
Show/Hide Text Ruler
[ Hide ]
If [ Get ( AccountName ) = "Admin" ]
Show/Hide Status Area
[ Hide ]
Install Menu Set [ “[Standard FileMaker Menus]” ]
Else
Show/Hide Status Area
[ Lock; Hide ]
Install Menu Set [ “HGT” ]
End If
#
If [ $$import = 1 ]
Set Variable [ $$import ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Perform Script [ “defaultNodeMenu” ]
Show Custom Dialog [ Message: "Import is almost complete! Now select yourself as the default node (the one creating new records). Last, select the default copyright and your import will be done!"; Buttons: “OK” ]
#
End If
#
January 28, 平成26 17:32:13 Empty Library.fp7 - startDatabase -2-
