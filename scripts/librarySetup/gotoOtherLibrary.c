October 8, 2018 14:59:21 Library.fmp12 - gotoOtherLibrary -1-
librarySetup: gotoOtherLibrary
#
#
#
#DON'T WORRY!!! Ignore the $$path not found
#error. :-) This path is dynamically set
#at the end of this script. IF YOU CREATE
#new apps for HGT, make sure to add the
#otherLibrary $$path variable as an external
#data source for those apps from the File menu:
#File > Manage > External Data Sources
#Name: otherLibrary
#Details: File Path: $$path
#
#
#
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#
#This script needs to be kept identical
#to the same script in ALL HGT Apps!
#
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#
#
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
Show Custom Dialog [ Message: "The library you selected is not available on this device or its name was changed so its
shortcut is being deleted."; Default Button: “OK”, Commit: “No” ]
#Tell user how to add a library.
Show Custom Dialog [ Message: "You can add it back after locating it using the add button."; Default Button: “OK”, Commit:
“No” ]
Delete Portal Row
[ No dialog ]
Exit Script [ ]
End If
#
#Close all solutions window if open after selecting a library.
Close Window [ Name: "All Apps"; Current file ]
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
removed from this list. You can add it back after locating it using the add button."; Default Button: “OK”, Commit: “No” ]
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
#Not sure why this code is here anymore.
#It was causing the browser to open once
#I upgraded to FM17, and the script seems
#to function without it, so I am disabling
#it for now. Can delete it once beta
#testing is done.
// #Select the current library windows if open and selected.
// If [ MemorySwitch::currentLibraryPath = $path ]
// Select Window [ Name: GetValue ( WindowNames ( Case ( Get ( SystemPlatform ) = - 2 ;
MemorySwitch::name ;
MemorySwitch::name ) ) ; 1 ) ]
// Select Window [ Name: MemorySwitch::currentLibraryWIndows ]
// End If
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
If [ MemorySwitch::currentLibraryPath ≠ $path ]
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
removed from this list. You can add it back after locating it using the add button."; Default Button: “OK”, Commit: “No” ]
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
#Set selected path and name to current name
#and path.
Set Field [ MemorySwitch::currentLibraryPath; $path ]
Set Field [ MemorySwitch::currentLibraryName; $name ]
#
#This variable is essential to allow this script to
#activate the other library's script that will move
#all that library's windows to the front.
Set Variable [ $$path; Value:$path ]
#
#Close All Apps window if open after selecting a library.
If [ $$otherApps = 1 ]
Close Window [ Name: "All Apps"; Current file ]
Set Variable [ $$otherApps ]
#Perform the other library's window arranging script.
#The <unknown> will change to otherLibrary once the
#$$path variable above is defined.
Perform Script [ <unknown> from file: “otherLibrary” (file not open) ]
Halt Script
End If
#
#
