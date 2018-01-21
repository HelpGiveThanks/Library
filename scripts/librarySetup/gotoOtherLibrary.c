January 11, 2018 18:38:37 Library.fmp12 - gotoOtherLibrary -1-
librarySetup: gotoOtherLibrary
#
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#This script needs to be kept identical to the
#same script in the ActionLog.
#
#Because this portal is to external database it is
#essential to get this record's path info for use in
#other script steps.
Set Variable [ $path; Value:MemorySwitch::path ]
Set Variable [ $name; Value:MemorySwitch::name ]
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Set Error Capture [ On ]
#
Set Field [ MemorySwitch::currentLibraryName; $name ]
Open URL [ "fmp://%7e/" & Substitute ( MemorySwitch::name ; " " ; "%20" ) ]
[ No dialog ]
#
If [ Get ( LastError ) ≠ 0 ]
#If the library fails to open inform user why.
Show Custom Dialog [ Message: "Click the folder icon (top left corner) to start a library and add it to this menu. The one you
selected is not available on this device or its name was changed so this shortcut is being deleted."; Default Button: “OK”,
Commit: “No” ]
Delete Portal Row
[ No dialog ]
Exit Script [ ]
End If
#
#Close all solutions window if open after selecting a library.
Close Window [ Name: "All Solutions"; Current file ]
Set Variable [ $$otherApps ]
Halt Script
#
End If
#
#If library path is blank (which should only happen if
#admin adds library manually with path), then delete
#this library name from the list.
If [ MemorySwitch::path = "" ]
Show Custom Dialog [ Message: "This library file cannot be found under the name " & MemorySwitch::name & ". It will be
removed from this list. You can add it back by going to its folder on your PC and double clicking on it."; Default Button: “OK”,
Commit: “No” ]
#
#This seems to work if just the portal row is
#deleted. Further testing is needed to confirm.
Delete Portal Row
[ No dialog ]
#
// #ISSUE: If you have a portal into a table that is more
// #than one relationship away, and if that related table
// #exists in an external file, then you cannot delete
// #the portal row.
// Go to Portal Row [ $row ]
[ No dialog ]
// Delete Record/Request
[ No dialog ]
// Delete Portal Row
[ No dialog ]
#
#Because the one step above seems to work, I
#am disabling these next steps for deleting a
#portal row.
// Go to Layout [ <unknown> ]
// Show All Records
// Go to Record/Request/Page
[ First ]
// Loop
// Exit Loop If [ $path = MemorySwitch::path ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ $path = MemorySwitch::path ]
// Delete Record/Request
[ No dialog ]
// End If
// Go to Layout [ <unknown> ]
Exit Script [ ]
End If
#
#Select the current library windows if open and selected.
If [ MemorySwitch::currentLibraryPath = $path ]
Select Window [ Name: GetValue ( WindowNames ( Case ( Get ( SystemPlatform ) = - 2 ;
MemorySwitch::name ;
MemorySwitch::name ) ) ; 1 ) ]
Select Window [ Name: GetValue ( WindowNames ( Case ( Get ( SystemPlatform ) = - 2 ;
MemorySwitch::name ;
MemorySwitch::name ) ) ; 2 ) ]
Select Window [ Name: MemorySwitch::currentLibraryMainWIndow ]
End If
#
#There is no harm in leaving multiple libraries
#open, so just open the selected one if
#available. NOTE: There are too many
#different window names that could be open
#for a library, and further testing needs to be
#done make sure all are accounted for before
#closing an open library is a sure thing!
// #If the library selected is not open, then close the current
// #library, which means closing all of its windows, and
// #then open the selected library.
If [ MemorySwitch::currentLibraryPath ≠ $path or Get (LastError) = 112 ]
#
// Set Variable [ $number; Value:1 ]
// Loop
// Loop
// Close Window [ Name: Case (
$number = 1 ; "Setup" ;
$number = 2 ; "References" ;
$number = 3 ; "Test" ;
$number = 4 ; "Learn" ;
$number = 5 ; "Report" ;
$number = 6 ; "Tag Menus" ) ]
// Exit Loop If [ Get (LastError) = 112 ]
// End Loop
// Set Variable [ $number; Value:$number + 1 ]
// Exit Loop If [ $number = 7 ]
// End Loop
#
Set Field [ MemorySwitch::currentLibraryPath; $path ]
Set Field [ MemorySwitch::currentLibraryName; $name ]
Open URL [ Case ( Get ( SystemPlatform ) = - 2 ;
Substitute (MemorySwitch::path ; " " ; "%20" ) ;
Substitute ( Substitute ( MemorySwitch::path ; "file:/" ; "file://" ) ; " " ; "%20" ) ) ]
[ No dialog ]
End If
#
#If the path stored for the selected library failed to open
#the library, then that library is no longer there or its
#name has been changed, so delete it from the
#library list.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This library file cannot be found under the name " & MemorySwitch::name & ". It will be
removed from this list. You can add it back by going to its folder on your PC and double clicking on it."; Default Button: “OK”,
Commit: “No” ]
#
#This seems to work if just the portal row is
#deleted. Further testing is needed to confirm.
Delete Portal Row
[ No dialog ]
#
// #ISSUE: If you have a portal into a table that is more
// #than one relationship away, and if that related table
// #exists in an external file, then you cannot delete
// #the portal row.
// Go to Portal Row [ $row ]
[ No dialog ]
// Delete Record/Request
[ No dialog ]
// Delete Portal Row
[ No dialog ]
#
#Because the one step above seems to work, I
#am disabling these next steps for deleting a
#portal row.
// Go to Layout [ <unknown> ]
// Show All Records
// Go to Record/Request/Page
[ First ]
// Loop
// Exit Loop If [ $path = MemorySwitch::path ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ $path = MemorySwitch::path ]
// Delete Record/Request
[ No dialog ]
// End If
// Go to Layout [ <unknown> ]
Exit Script [ ]
End If
#
#Close other solutions window if open after selecting a library.
If [ $$otherApps = 1 ]
Close Window [ Name: "All Solutions"; Current file ]
Set Variable [ $$otherApps ]
Halt Script
End If
#
