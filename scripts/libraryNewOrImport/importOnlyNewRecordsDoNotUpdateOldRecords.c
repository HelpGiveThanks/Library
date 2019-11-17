October 30, 2019 13:53:12 Library.fmp12 - -1-
importOnlyNewRecordsDoNotUpdateOldRecords
libraryNewOrImport: importOnlyNewRecordsDoNotUpdateOldRecords
#
#PURPOSE: Import ONLY Learn records from another
#library into this library file, and overwrites
#existing records with imported library's
#changes.
#
#
#Prevent user from importing data into a
#branch library. This is a safeguard to help
#users keep track of which library has the
#most complete record set = main library; AND
#make sure user's don't overwrite new records
#with old records.
If [ tempSetup::userLibraryMainOrBranch = 1 ]
Show Custom Dialog [ Message: "This is a branch library. Import branch library records into the main library. Then replace
branch libraries (libraries on other devices) with duplicates of the udpated main library file." ]
Show Custom Dialog [ Message: "By importing all branches into your main library; then replacing them with duplicates of the
main library, you insure duplicate, consolidated, up-to-date libraries on all your devices." ]
Show Custom Dialog [ Message: "IMPORTANT!!! After you duplicate the main library, 1) make sure you open it, 2) go to the
Setup Tag Menu's AllDefaults menu, 3) and check the branch-library checkbox." ]
Exit Script [ ]
End If
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Inform the user the import will both add new
#records and overwrite existing records with
#changes made in library being imported.
Show Custom Dialog [ Message: "IMPORTANT: This import will only add new and update, overwrite, etc. old LEARN records and
TEST RESULT records. Reference and Tag records will not be updated or added."; Default Button: “OK”, Commit: “No”; Button 2:
“cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Inform user to make a backup of the current
#library before importing new data as this
#process can crash FileMaker which can
#damage the main library file.
Show Custom Dialog [ Message: "On some imports FileMaker crashes, so, a backup of this main Library file MUST be created before
proceeding. Click OK to create a backup."; Default Button: “OK”, Commit: “No”; Button 2: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Create a copy of this library file.
Save a Copy as [ Create directories:No ]
[ copy of current file ]
If [ Get ( LastError ) = 1 ]
Exit Script [ ]
End If
Show Custom Dialog [ Message: "If FileMaker crashes during the import, delete this crashed main-library file, and try again with the
backup you just created."; Default Button: “OK”, Commit: “No”; Button 2: “cancel”, Commit: “No” ]
#
#If user clicks cancel then exit
#this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
Show Custom Dialog [ Message: "Do not be discouraged if FileMaker crashes several times in a row. Eventually, it will work. Always
delete the crashed library, and use the fresh copy just created to import into."; Default Button: “OK”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No” ]
#
#If user clicks cancel then exit
#this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Get library's ID and name, and the library
#creator and test subject node IDs and names.
#This is done so that later on in the script the
#imported library's ID record can be deleted, if
#there is one, and any name changes can be
#captured and reported to the user.
Set Variable [ $libraryID; Value:TEMP::klibrary ]
Set Variable [ $$libraryNameForNameChangeCheck; Value:TEMP::userLibraryName ]
Set Variable [ $$primaryNodeNameChangeCheck; Value:TEMP::DEFAULTNodePrimaryName ]
Set Variable [ $$testSubjectNodeNameChangeCheck; Value:TEMP::DEFAULTNodeTestSubjectName ]
#
#
#Get path of library that user wants to import
#files from by generating this code and
#cuting it using the computer's clipboard so
#it can be pasted by the library the user is now
#opening (the one they want to import files
#from).
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::backup; Case (tempSetup::InventoryLibraryYN[1] ; 1 ; 2 ) & "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.
eupqoiwendssasdeawsrre5o983498woeirf" ]
#
#Cut instead of copy, saves the step of erasing
#this code from the current file, as the copy
#command both copies and erases the code.
Cut [ backup::backup ]
[ Select ]
#
#Ask the user what file they want to
#import from. Because it is an (unknown) file,
#the user will be prompted to select this file.
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Open File [ <unknown> ]
#
#If user clicks cancel then exit
#this script.
If [ Get (LastError) = 1 ]
Exit Script [ ]
End If
#
#Make sure the file the user selected to import
#from was opened and its filepath copied. If it
#was already open, then this script did not
#open it and its startDatabase script did not
#just run and insert this code, which would
#have resulted in its filepath being copied by
#the computer's clipboard. Thus the
#computer's clipboard will still contain the
#copy-filepath code, instead of the file's
#filepath.
Go to Layout [ “backup” (backup) ]
Paste [ backup::backup ]
[ Select; No style ]
#
#
If [ Case (tempSetup::InventoryLibraryYN[1] ; 1 ; 2 ) & "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.
eupqoiwendssasdeawsrre5o983498woeirf" = backup::backup ]
#
#Tell the user the import failed and how to
#succeed. Then restart the library to all the
#user to try again.
Set Field [ backup::backup; "" ]
#Important!!! Clear the clipboard!
Copy [ ]
[ Select ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Show Custom Dialog [ Message: "Open library's records cannot be imported. 1) Close the library you're trying to import. 2) Click
the import button." ]
Exit Script [ ]
End If
#
#
#
#In the startDatabase script an if calc
#determines if the library being imported is of a
#type (idea or inventory) that is the opposite of
#the import-into library. If it is the opposite
#type, then the word 'idea' or 'inventory' is
#pasted into the import-into library's backup
#field, so that the import can be stopped.
If [ "ideas" = backup::backup ]
#
Set Field [ backup::backup; "" ]
#Important!!! Clear the clipboard!
Copy [ ]
[ Select ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Show Custom Dialog [ Message: "The library selected for import is an idea library. This library is an inventory library. Idea
library records cannot be imported into an inventory library." ]
#
Exit Script [ ]
Else If [ "inventory" = backup::backup ]
#
Set Field [ backup::backup; "" ]
#Important!!! Clear the clipboard!
Copy [ ]
[ Select ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Show Custom Dialog [ Message: "The library selected for import is an inventory library. This library is an idea library. Inventory
library records cannot be imported into an idea library." ]
Exit Script [ ]
#
#
#This next bit cannot work as there is no way to
#insure the computers universal clipboard was
#used by FileMaker or the user during
#the import process.
// Else If [ "failure" = backup::backup ]
// Set Field [ backup::backup; "" ]
// Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
// Show Custom Dialog [ Message: "The computer's clipboard contents where changed during the import, which caused this
import attempt to fail. Please try again." ]
// Show Custom Dialog [ Message: "IMPORTANT!!! Do not user the cut or copy commands during the import process." ]
// Exit Script [ ]
#
#
#
#If the computer's clipboard contains a
#filepath, then proceed with the import.
Else
Set Variable [ $filepath; Value:backup::backup ]
#Important!!! Clear the clipboard!
Set Field [ backup::backup; "" ]
Copy [ ]
[ Select ]
End If
#
#
#Import learn and test result records.
Go to Layout [ “tableTestLearn” (testlearn) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “testlearn”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1
import to testlearn::_Ltestlearn
Source field 2 import to testlearn::ktestSubject
Source field 3 import to testlearn::_Number
Source field 4 import to testlearn::ktestSubsection
Source field 5 import to testlearn::note
Source field 6 import to testlearn::picture
Source field 7 import to testlearn::subsectionCustomName
Source field 8 import to testlearn::kcInUseOnReportSubsection
Source field 9 import to testlearn::ktestSection
Source field 10 import to testlearn::countOfALLSubsectionsTestResults
Source field 11 import to testlearn::checkboxCaption
Source field 12 import to testlearn::recordnumberglobal
Source field 13 import to testlearn::recordcountglobal
Source field 14 import to testlearn::countOfONESubsectionsTestResults
Source field 15 import to testlearn::rateORgradeTestResult
Source field 16 import to testlearn::kclibrary
Source field 17 import to testlearn::kshowReferencedMedia
Source field 18 import to testlearn::kreportNumber
Source field 19 import to testlearn::timestamp
Source field 21 import to testlearn::orderTestResult
Source field 22 import to testlearn::kcKeywordOther
Source field 23 import to testlearn::kNodeOther
Source field 24 import to testlearn::kcopyright
Source field 25 import to testlearn::kNodePrimary
Source field 26 import to testlearn::kKeywordPrimary
Source field 27 import to testlearn::OtherKeyWords
Source field 28 import to testlearn::NodeOthers
Source field 29 import to testlearn::URL
Source field 30 import to testlearn::kcreference
Source field 32 import to testlearn::filterFind
Source field 33 import to testlearn::kRecordCreatorNode
Source field 34 import to testlearn::kRecordModifierNode
Source field 35 import to testlearn::dateModify
Source field 36 import to testlearn::incomplete
Source field 38 import to testlearn::copyrightYear
Source field 39 import to testlearn::kcbrainstorm
Source field 40 import to testlearn::kgtestSection
Source field 41 import to testlearn::kctestSubsectionInfo
Source field 42 import to testlearn::orderTestInformation
Source field 43 import to testlearn::kctestResultCheckedItems
Source field 45 import to testlearn::brainstormCasePoint
Source field 48 import to testlearn::pictureThumbnail ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “testlearn”; Method: Update matching; Add remaining; Character Set: “Unicode”;
Field Mapping: Source field 1 match with testlearn::_Ltestlearn
Source field 2 import to testlearn::ktestSubject
Source field 3 import to testlearn::_Number
Source field 4 import to testlearn::ktestSubsection
Source field 5 import to testlearn::note
Source field 6 import to testlearn::picture
Source field 7 import to testlearn::subsectionCustomName
Source field 8 import to testlearn::kcInUseOnReportSubsection
Source field 9 import to testlearn::ktestSection
Source field 10 import to testlearn::countOfALLSubsectionsTestResults
Source field 11 import to testlearn::checkboxCaption
Source field 12 import to testlearn::recordnumberglobal
Source field 13 import to testlearn::recordcountglobal
Source field 14 import to testlearn::countOfONESubsectionsTestResults
Source field 15 import to testlearn::rateORgradeTestResult
Source field 16 import to testlearn::kclibrary
Source field 17 import to testlearn::kshowReferencedMedia
Source field 18 import to testlearn::kreportNumber
Source field 19 import to testlearn::timestamp
Source field 21 import to testlearn::orderTestResult
Source field 22 import to testlearn::kcKeywordOther
Source field 23 import to testlearn::kNodeOther
Source field 24 import to testlearn::kcopyright
Source field 25 import to testlearn::kNodePrimary
Source field 26 import to testlearn::kKeywordPrimary
Source field 27 import to testlearn::OtherKeyWords
Source field 28 import to testlearn::NodeOthers
Source field 29 import to testlearn::URL
Source field 30 import to testlearn::kcreference
Source field 32 import to testlearn::filterFind
Source field 33 import to testlearn::kRecordCreatorNode
Source field 34 import to testlearn::kRecordModifierNode
Source field 35 import to testlearn::dateModify
Source field 36 import to testlearn::incomplete
Source field 38 import to testlearn::copyrightYear
Source field 39 import to testlearn::kcbrainstorm
Source field 40 import to testlearn::kgtestSection
Source field 41 import to testlearn::kctestSubsectionInfo
Source field 42 import to testlearn::orderTestInformation
Source field 43 import to testlearn::kctestResultCheckedItems
Source field 45 import to testlearn::brainstormCasePoint
Source field 48 import to testlearn::pictureThumbnail ]
[ No dialog ]
End If
#
#
#
#Erase codes that trigger new
#library creation script steps.
Go to Layout [ “backup” (backup) ]
Set Field [ backup::backup; "" ]
Set Field [ backup::newLibrary; "" ]
#
#Inform the user the import was successful
#after restarting the database and upload
#the new record information.
# This variable will trigger the success
#dialogue box.
Set Variable [ $$addRecords; Value:1 ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
#
#Restart database to insure updated file's
#information are used for this library's temp
#fields and variables.
Show Custom Dialog [ Message: "Library will now restart to reset values that could have changed due to changes made during
import." ]
Perform Script [ “startDatabase” ]
#
#
