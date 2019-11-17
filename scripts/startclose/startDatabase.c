October 31, 2019 17:40:14 Library.fmp12 - startDatabase -1-
startclose: startDatabase
#
#PURPOSE: Manage the 4 script newLibrary
#creation process, OR open the library.
#
#BEGIN: Manage new library creation process.
#
#Check if database is being started by any of
#the newLibrary scripts.
Set Window Title [ Current Window; New Title: "Library Update" ]
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
#
#If this is a new copy of the library created by the
#newLibraryStep1createACopyOfThisLibraryFile
#script, then it will have this erase-records
#code in the newLibrary field. Proceed with
#step 2 of creating a new library file, rather
#than starting up this copy of the library as
#ready to use library file.
If [ backup::newLibrary = "234874920347574weidf792342f9823984" ]
Perform Script [ “newLibraryStep2_EraseRecordsInCopyOfLibrary” ]
Exit Script [ ]
End If
#
#If user is opening a just-copied library file
#(step 1 of the newLibrary creation process),
#has just had all its records erased (step 2),
#then ask the user how to proceed: perform
#step 3A (new library) or step 3B (upgrade old
#library to this library's version)?
If [ backup::newLibrary = "newLibrary" ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Show Custom Dialog [ Message: "1) Create a new, empty library." & ¶ &
"2) Import another library's records into version " & tempSetup::versionNumber & " of the library application."; Default Button:
“new”, Commit: “Yes”; Button 2: “import”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
#
#If the user cancels, then close this new file as
#the user cannot do anything with a new
#library until they decide to use it as a new/
#empty library or to import another library's
#data into it = upgrade.
If [ Get ( LastMessageChoice ) = 3 ]
Show Custom Dialog [ Message: "When you are ready to decide what to do with this empty library re-open it. This library
will now close."; Default Button: “OK”, Commit: “Yes” ]
Close Window [ Current Window ]
Exit Script [ ]
#
#Perform step 3A if the user clicks new.
Else If [ Get ( LastMessageChoice ) = 1 ]
Perform Script [ “newLibraryStep3A_makeEmptiedLibraryANewLibrary” ]
Exit Script [ ]
#
#Perform step 3B if the user clicks import.
Else If [ Get ( LastMessageChoice ) = 2 ]
Perform Script [ “newLibraryStep3B_importLibraryIntoEmptiedLibrary” ]
Exit Script [ ]
End If
End If
#
#Check if this library file is being started
#by an import script. If it is, the computer's
#clipboard will contain this hopefully
#impossible to get code from anywhere but the
#library's two import scripts. This code tells
#this library that it was opened only to
#get its filepath. This filepath will be used
#after this library file is closed by the library
#file that opened it to import it records.
Paste [ backup::backup ]
[ Select ]
Set Variable [ $ideasORthingsLibrary; Value:Left ( backup::backup ; 1 ) ]
Set Variable [ $importCode; Value:Middle ( backup::backup ; 2 ; 999 ) ]
Set Field [ backup::backup; $importCode ]
#
#
#In the importDataFromABranchIntoThisMainLibrary
#script an if calc determines if the library being
#imported into is the opposite type (idea or
#inventory) of this library. If it is the opposite
#type, then the word 'idea' or 'inventory' is
#pasted into the import-into library's backup
#field, and then cut, and pasted into the library
#these records are being imported into, so that
#the import can be stopped.
If [ backup::backup = "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" ]
#If library asking for import is a new library, and
#so neither an idea or inventory library, then
#proceed with getting filepath for this library,
#and skip these exit import script steps.
If [ Case (tempSetup::InventoryLibraryYN[1] ; 1 ; 2 ) ≠ $ideasORthingsLibrary
 and
0 ≠ $ideasORthingsLibrary ]
Set Field [ backup::backup; Case (tempSetup::InventoryLibraryYN[1] ; "inventory" ; "ideas" ) ]
Cut [ backup::backup ]
[ Select ]
Perform Script [ “closeLibrary” ]
Exit Script [ ]
#
#
#
#
#If this library is OK to import, then copy its file
#path so that the importing library can have its
#file path for the script
#importDataFromABranchIntoThisMainLibrary
#to complete the import process.
Else
Set Field [ backup::backup; "" ]
Copy [ backup::filepath ]
[ Select ]
#
#Prepare to import TEMP fields by making sure
#there is a record to import.
Go to Layout [ “tableTemp” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Perform Script [ “closeLibrary” ]
Exit Script [ ]
End If
End If
#
#
#This next bit cannot work as there is no way to
#insure the computers universal clipboard was
#used by FileMaker or the user during
#the import process.
// If [ backup::backup ≠ "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf"
 and
backup::backup ≠ "" ]
// Set Field [ backup::backup; "failure" ]
// Cut [ backup::backup ]
[ Select ]
// Perform Script [ “closeLibrary” ]
// Exit Script [ ]
// End If
#
#
#END: Manage new library creation process.
#
#
#
#BEGIN: Open library.
#
#Start database with just one window. This is
#essential if user decides to restart the
#database. This step eliminates the possibility
#of extra windows.
Loop
Exit Loop If [ ValueCount ( WindowNames ( Get ( FileName ) ) ) = 1 ]
Close Window [ Current Window ]
End Loop
#
#FileMakerGO has a bug and will not complete
#the gotoOtherLibrary script, when the library
#selected is not yet open. This step, closes
#that window.
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
// Close Window [ Name: "All Apps" ]
#
#Set zoom level to 100%.
Set Zoom Level [ 100% ]
#
#Resize window just in case it is a 1x1 point window!
Move/Resize Window [ Current Window; Height: Get (WindowDesktopHeight) - 21; Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
#
#Clear these variables.
Set Variable [ $$add ]
Set Variable [ $$pause ]
Set Variable [ $$tagtest ]
Set Variable [ $$stopAdd ]
Set Variable [ $$tagLayout ]
Set Variable [ $$timeRecord ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$returnWindow ]
Set Variable [ $$goBackToSetup ]
Set Variable [ $$stopChangeName ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$lockedMainRefRecord ]
Set Variable [ $$doNotHaltOtherScripts ]
Set Variable [ $$userInCopyrightWindow ]
Set Variable [ $$lockedMainLearnRecord ]
Set Variable [ $$stopOpenNewTextWindow ]
Set Variable [ $$showFTmessageOnlyOnce ]
Set Variable [ $$stopLoadingTestSubSection ]
Set Variable [ $$lockedMainSubsectionRecord ]
Set Variable [ $$showCreatorNodemessageOnlyOnce ]
#
#Clear test temporary template fields.
Set Field [ TEMP::reportNumber; "" ]
Set Field [ TEMP::DEFAULTSectionName; "" ]
Set Field [ TEMP::kdefaultSectionTemplate; "" ]
#IMPORTANT!!! DO NOT clear the test subject!
#Warning messages are affected if cleared, and
#in general user will be annoyed because the
#test subject will show as selected in the Setup
#Node menu, but will not show up anywhere
#else as the library knows what test subject is
#selected thru this temp variable.
// Set Field [ TEMP::DEFAULTNodeTestSubjectName; "" ]
#
#Clear the message remember variable. They
#are used to show user a message only once
#per session.
Set Variable [ $$rememberTestItemChoice ]
Set Variable [ $$showReportItemCommentOnce ]
Set Variable [ $$stopShowingTestItemLockMessage ]
#
#Force system to calculate new values if
#needed by deleting current and creating new
#default's record.
Go to Layout [ “tableTemp” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
#
#
#Get library ID if this key field is blank.
Set Error Capture [ On ]
Allow User Abort [ Off ]
If [ TEMP::klibrary = "" or TEMP::userLibraryName = "" ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::match; "library" ]
Perform Find [ ]
#
Set Field [ TEMP::klibrary; testSubsectionGroup::_Lgroup ]
Set Field [ TEMP::userLibraryName; testSubsectionGroup::name ]
Set Field [ TEMP::userLibraryVersionNumber; testSubsectionGroup::versionNumber ]
End If
#
#Re-title and re-size main library setup window.
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Set Window Title [ Current Window; New Title: "Setup" ]
Show/Hide Text Ruler
[ Hide ]
If [ Get ( SystemPlatform ) = - 2 ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Else
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
End If
Go to Field [ ]
#
#Show all library setup references and sort
#them by date so focus is on most current
#setup reference.
Show All Records
Sort Records [ Keep records in sorted order; Specified Sort Order: aboutLibraryMain::publicationDate; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Make sure library's creator node and
#its tag node group exists.
Perform Script [ “CHUNK_checkCreatorNodeAndPrimaryNode” ]
#
#Insure filelocation records are present,
#and default copyright tags.
Perform Script [ “CHUNK_CopyrightLockedFields” ]
#
#Insure during last session, user didn't drag
#new spellings into locked tag records.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#View as a form, instead of a table,
#to give the user a nicer experience.
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
View As
[ View as Form ]
Show All Records
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “CHUNK_checkForDraggedPasteChanges” ]
#
#Return to list view for admin users.
View As
[ View as List ]
#
#Open Setup's Tag-Menus window.
If [ Get ( SystemPlatform ) = - 2 ]
New Window [ Style: Document; Name: "Tag Menus"; Using layout: <Current Layout>; Height: Get (ScreenHeight); Width: Get
(ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2; Close: Yes; Minimize: Yes; Maximize: Yes; Resize: Yes; Menu Bar:
No; Dim parent window: No; Toolbars: No ]
Else
New Window [ Style: Document; Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get
(ScreenWidth) / 2; Close: Yes; Minimize: Yes; Maximize: Yes; Resize: Yes ]
End If
#
#Show regular menus if Admin logs in only.
If [ Get ( AccountName ) = "Admin" ]
Go to Layout [ “defaultsAll” (tempSetup) ]
Show/Hide Menubar
[ Show ]
Show/Hide Toolbars
[ Hide ]
Select Window [ Name: "Setup"; Current file ]
Show/Hide Toolbars
[ Hide ]
Print Setup [ Orientation: Portrait; Paper size: 8.5" x 11111" ]
[ Restore; No dialog ]
Else
Go to Layout [ “defaultsAll” (tempSetup) ]
Show/Hide Toolbars
[ Lock; Hide ]
Select Window [ Name: "Setup"; Current file ]
Show/Hide Toolbars
[ Lock; Hide ]
Print Setup [ Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore; No dialog ]
End If
#
#Set library defaults.
Perform Script [ “defaultLibraryButton” ]
If [ tempSetup::InventoryLibraryYN = "" and tempSetup::InventoryLibraryYN[2] = "" ]
#Set default layout views for
#a reference library.
Set Field [ tempSetup::layoutLtagK; "" ]
Set Field [ tempSetup::layoutRtagK; "" ]
Set Field [ tempSetup::layoutLtagN; "" ]
Set Field [ tempSetup::layoutRtagN; "" ]
#
#Designate library as a reference library.
Set Field [ libraryNameAndInfo::orderOrLibraryType; "" ]
Set Field [ TEMP::InventoryLibraryYN[2]; 1 ]
End If
#
#Set test section to hide FT results.
Set Field [ TEMP::testHideFormTextItemsFTs; 1 ]
#
#Tell other databases to go to this library
#when user clicks the 'library' button in
#another Help Give Thanks database.
Set Field [ MemorySwitch::currentLibraryWIndows; "Setup" ]
Set Field [ MemorySwitch::currentLibraryWIndows[2]; "Tag Menus" ]
Set Field [ MemorySwitch::currentLibraryWIndows[3]; "" ]
Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
#
#Recalculate help filepath. To do this,
#filemaker must create a new record which
#can then be deleted. The help filepath is a
#global record, and that means the
#recaclucated path will now be used for all
#memoryswitch records and scripts needing
#this path.
New Record/Request
Delete Record/Request
[ No dialog ]
Show All Records
#
Go to Record/Request/Page
[ First ]
Loop
If [ Get (SystemPlatform) = 3 ]
Exit Loop If [ Get ( FileName ) = MemorySwitch::name ]
Else
Exit Loop If [ Get ( FilePath ) = MemorySwitch::path or Get ( FileName ) = MemorySwitch::name and MemorySwitch::path =
"" ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#On the iPhone/iPad, leave the path field
#blank. This script will add the path when
#used on a desktop/laptop. This allows one
#record per library, using the name to find it
#on iDevices and the path to find it on full
#computers.
If [ Get ( FileName ) = MemorySwitch::name and MemorySwitch::path = "" and Get (SystemPlatform) ≠ 3 ]
Set Field [ MemorySwitch::path; TEMP::filePath ]
Else If [ Get ( FileName ) ≠ MemorySwitch::name and Get ( FilePath ) ≠ MemorySwitch::path and Get (SystemPlatform) ≠ 3 ]
New Record/Request
Set Field [ MemorySwitch::path; TEMP::filePath ]
Set Field [ MemorySwitch::name; TEMP::fileName ]
Else If [ Get ( FileName ) ≠ MemorySwitch::name and Get (SystemPlatform) = 3 ]
New Record/Request
Set Field [ MemorySwitch::name; TEMP::fileName ]
End If
#
#Get file path and name.
Set Field [ MemorySwitch::currentLibraryPath; Get ( FilePath ) ]
Set Field [ MemorySwitch::currentLibraryName; TEMP::fileName ]
#
#Report version number to Memory Switch Table.
Set Field [ MemorySwitch::versionLibrary; tempSetup::versionNumber ]
#
#Go to the main layout.
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
#
#Show regular menus if Admin logs in and set
#print page size for one long page so when
#generating PDFs for GitHub a script's title will
#be shown only once (it shows multiple times if
#the script takes several letter size pages).
Show/Hide Text Ruler
[ Hide ]
If [ Get ( AccountName ) = "Admin" ]
Show/Hide Toolbars
[ Hide ]
Show/Hide Menubar
[ Show ]
Install Menu Set [ “[Standard FileMaker Menus]” ]
Print Setup [ Orientation: Portrait; Paper size: 8.5" x 1000" ]
[ Restore; No dialog ]
Show Custom Dialog [ Message: "Welcome Admin user! Page setup for admin's is an extra-long page, so PDFs of scripts can
be saved with zero page breaks for showing scripts on GitHub."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "IMPORTANT!!! Due to changes in FileMaker, script line-spaces no longer require # symbols,
which are required to keep line spaces in GitHub."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Please add # and one space (spacebar click) to insure blank line spacing is maintained in any
scripts that you edit! This includes old scripts! Please, add these # back into them. THANKS!!!"; Default Button: “OK”,
Commit: “Yes” ]
Else
Show/Hide Toolbars
[ Lock; Hide ]
Install Menu Set [ “HGT” ]
Print Setup [ Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore; No dialog ]
End If
#
#Warn user if the library files are on the
#desktop and not in a folder.
If [ PatternCount ( Get (FilePath) ; "/desktop/" & Get ( FileName )) ]
Show Custom Dialog [ Message: "This library will not work properly from the destop of your computer. It needs to go in its own
folder, inside the folder where the ActionLog and Reference files are located. Click ? for more information."; Default Button:
“OK”, Commit: “Yes” ]
End If
#
#Finish setting up the new library.
If [ $$newLibraryNextSteps = 1 ]
Set Variable [ $$newLibraryNextSteps ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “defaultNodeMenu” ]
Show Custom Dialog [ Message: "Your new library is almost ready! Change the name of the first node to your name since you
will be the creator of new library records."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Select the default copyright for your new records, and last, click 'main' and change the name of
library X to make this library ready for use."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#Finish the upgrade to a new library file.
If [ $$import = 1 ]
Set Variable [ $$import ]
#
#Force remaking of picture thumbnails to sure
#all pictures have thumbnails with the current
#database's specified dimensions.
Perform Script [ “Interactivate” ]
Select Window [ Name: "Tag Menus"; Current file ]
Show Custom Dialog [ Message: "Import is complete! Make sure you're selected as the primary node (the one creating new
records), and check your selected copyright!"; Default Button: “OK”, Commit: “Yes” ]
Perform Script [ “defaultNodeMenu” ]
End If
#
#Finish the import of new records.
If [ $$addRecords = 1 ]
#
#Force remaking of picture thumbnails to sure
#all pictures have thumbnails with the current
#database's specified dimensions.
Set Variable [ $$addRecords ]
Perform Script [ “Interactivate” ]
Show Custom Dialog [ Message: "Successful import! Delete the backup file created before this import. It now lacks the files, just
imported. Of course, it is always good to regularly backup your most current Library file."; Default Button: “OK”, Commit:
“No” ]
#
#
#Inform the user if this library's name
#was changed.
If [ $$libraryNameWASChanged ≠ "" ]
Show Custom Dialog [ Message: "This library's name was changed during the import from " & $
$libraryNameForNameChangeCheck & " to " & $$libraryNameWASChanged & "."; Default Button: “OK”, Commit: “No” ]
End If
#
#Inform the user if the primary node's name
#was changed.
If [ TEMP::DEFAULTNodePrimaryName ≠ $$primaryNodeNameChangeCheck ]
Show Custom Dialog [ Message: "This library's primary node's name was changed during the import from " & $
$primaryNodeNameChangeCheck & " to " & TEMP::DEFAULTNodePrimaryName & "."; Default Button: “OK”, Commit:
“No” ]
End If
#
#Inform the user if the test subject's name
#was changed.
If [ TEMP::DEFAULTNodeTestSubjectName ≠ $$testSubjectNodeNameChangeCheck ]
Show Custom Dialog [ Message: "This library's test subject node's name was changed during the import from " & $
$testSubjectNodeNameChangeCheck & " to " & TEMP::DEFAULTNodeTestSubjectName & "."; Default Button: “OK”,
Commit: “No” ]
End If
#
Set Variable [ $$libraryNameWASChanged ]
Set Variable [ $$primaryNodeNameChangeCheck ]
Set Variable [ $$libraryNameForNameChangeCheck ]
Set Variable [ $$testSubjectNodeNameChangeCheck ]
#
End If
#
#If there is only one node and it is the
#Admin node, the inform the user that they
#need to make a node for themselves.
If [ $$AdminOnlyNode = 1 ]
Show Custom Dialog [ Message: "IMPORTANT! Do create a node/author record for yourself, so that you will have a unique ID
associated with all the records that you create."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "When startup is complete 1) go to the Tag Menu window. 2) Click the node button. 3) Click
the P button next to your name to select yourself as the creator of all new library records."; Default Button: “OK”, Commit:
“Yes” ]
Else
Set Variable [ $$AdminOnlyNode ]
End If
#
#END: Open library.
#
#
