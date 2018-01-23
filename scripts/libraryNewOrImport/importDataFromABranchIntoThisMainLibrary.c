January 10, 2018 16:31:49 Library.fmp12 - importDataFromABranchIntoThisMainLibrary -1-
libraryNewOrImport: importDataFromABranchIntoThisMainLibrary
#
#PURPOSE: Import records from another
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
Show Custom Dialog [ Message: "IMPORTANT: Records changed — edited — in the import libary will change — update, overwrite,
etc. — records in this library."; Default Button: “OK”, Commit: “No”; Button 2: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
Show Custom Dialog [ Message: "For example, if the key tag 'Apple' in the main library is changed to 'Orange' in a branch library, then
'Apple' in main library will be changed to 'Orange' when that branch record is imported."; Default Button: “OK”, Commit: “No”;
Button 2: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Inform user to make a backup of the current
#library before importing new data as this
#process can crash FileMaker which can
#damage the main library file.
Show Custom Dialog [ Message: "On some imports FileMaker crashes, so, a backup of this main Library file MUST be created before
proceeding."; Default Button: “OK”, Commit: “No”; Button 2: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Create a copy of this library file.
Save a Copy as [ ]
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
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
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
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
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
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
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
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
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
// Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
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
#1) Import test section records.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “testSectionCreatedFromATemplate”; Method: Add; Character Set: “Unicode”; Field
Mapping: Source field 1 import to testSectionCreatedFromATemplate::ktestSubjectNode
Source field 2 import to testSectionCreatedFromATemplate::ksectionTemplate
Source field 3 import to testSectionCreatedFromATemplate::_LtestSection
Source field 4 import to testSectionCreatedFromATemplate::name
Source field 5 import to testSectionCreatedFromATemplate::inUse
Source field 6 import to testSectionCreatedFromATemplate::order
Source field 7 import to testSectionCreatedFromATemplate::_number
Source field 8 import to testSectionCreatedFromATemplate::klibrary
Source field 9 import to testSectionCreatedFromATemplate::reportNumber
Source field 10 import to testSectionCreatedFromATemplate::kcreatorNode
Source field 12 import to testSectionCreatedFromATemplate::creationDate
Source field 13 import to testSectionCreatedFromATemplate::creationTime ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “testSectionCreatedFromATemplate”; Method: Update matching; Add remaining;
Character Set: “Unicode”; Field Mapping: Source field 1 import to testSectionCreatedFromATemplate::ktestSubjectNode
Source field 2 import to testSectionCreatedFromATemplate::ksectionTemplate
Source field 3 match with testSectionCreatedFromATemplate::_LtestSection
Source field 4 import to testSectionCreatedFromATemplate::name
Source field 5 import to testSectionCreatedFromATemplate::inUse
Source field 6 import to testSectionCreatedFromATemplate::order
Source field 7 import to testSectionCreatedFromATemplate::_number
Source field 8 import to testSectionCreatedFromATemplate::klibrary
Source field 9 import to testSectionCreatedFromATemplate::reportNumber
Source field 10 import to testSectionCreatedFromATemplate::kcreatorNode
Source field 12 import to testSectionCreatedFromATemplate::creationDate
Source field 13 import to testSectionCreatedFromATemplate::creationTime ]
[ No dialog ]
End If
#
#
#2) Import test subsection records.
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “testSubsectionTemplate”; Method: Add; Character Set: “Unicode”; Field Mapping:
Source field 1 import to testSubsectionTemplate::_LtestSubsection
Source field 2 import to testSubsectionTemplate::ksubsectionGroup
Source field 3 import to testSubsectionTemplate::_number
Source field 4 import to testSubsectionTemplate::kcsections
Source field 5 import to testSubsectionTemplate::name
Source field 6 import to testSubsectionTemplate::order
Source field 7 import to testSubsectionTemplate::retire
Source field 8 import to testSubsectionTemplate::kgtestSubject
Source field 9 import to testSubsectionTemplate::gtestSectionNameGlobal
Source field 10 import to testSubsectionTemplate::gtestSubjectNameGlobal
Source field 11 import to testSubsectionTemplate::kgtestSection
Source field 12 import to testSubsectionTemplate::gprogressGlobal
Source field 13 import to testSubsectionTemplate::klibrary
Source field 14 import to testSubsectionTemplate::kgreportNumber
Source field 15 import to testSubsectionTemplate::mtestSubsection
Source field 16 import to testSubsectionTemplate::ktestItemGroup
Source field 17 import to testSubsectionTemplate::rule
Source field 18 import to testSubsectionTemplate::kcreatorNode
Source field 19 import to testSubsectionTemplate::kmodifierNode
Source field 20 import to testSubsectionTemplate::RecordModifyDate
Source field 21 import to testSubsectionTemplate::nameSpelling
Source field 22 import to testSubsectionTemplate::form ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “testSubsectionTemplate”; Method: Update matching; Add remaining; Character
Set: “Unicode”; Field Mapping: Source field 1 match with testSubsectionTemplate::_LtestSubsection
Source field 2 import to testSubsectionTemplate::ksubsectionGroup
Source field 3 import to testSubsectionTemplate::_number
Source field 4 import to testSubsectionTemplate::kcsections
Source field 5 import to testSubsectionTemplate::name
Source field 6 import to testSubsectionTemplate::order
Source field 7 import to testSubsectionTemplate::retire
Source field 8 import to testSubsectionTemplate::kgtestSubject
Source field 9 import to testSubsectionTemplate::gtestSectionNameGlobal
Source field 10 import to testSubsectionTemplate::gtestSubjectNameGlobal
Source field 11 import to testSubsectionTemplate::kgtestSection
Source field 12 import to testSubsectionTemplate::gprogressGlobal
Source field 13 import to testSubsectionTemplate::klibrary
Source field 14 import to testSubsectionTemplate::kgreportNumber
Source field 15 import to testSubsectionTemplate::mtestSubsection
Source field 16 import to testSubsectionTemplate::ktestItemGroup
Source field 17 import to testSubsectionTemplate::rule
Source field 18 import to testSubsectionTemplate::kcreatorNode
Source field 19 import to testSubsectionTemplate::kmodifierNode
Source field 20 import to testSubsectionTemplate::RecordModifyDate
Source field 21 import to testSubsectionTemplate::nameSpelling
Source field 22 import to testSubsectionTemplate::form ]
[ No dialog ]
End If
#
#
#3) Import learn and test result records.
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
#4) Import LIBRARY SETUP reference records.
Go to Layout [ “tableSetupReference” (setupReference) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “setupReference”; Method: Add; Character Set: “Unicode”; Field Mapping: Source
field 1 import to setupReference::_LlibrarySetupHowToCredit
Source field 2 import to setupReference::_Number
Source field 3 import to setupReference::URL
Source field 4 import to setupReference::publicationDate
Source field 5 import to setupReference::kcreatorNode
Source field 6 import to setupReference::name
Source field 7 import to setupReference::password
Source field 8 import to setupReference::klibrary
Source field 9 import to setupReference::version
Source field 13 import to setupReference::creatorName
Source field 14 import to setupReference::note ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “setupReference”; Method: Update matching; Add remaining; Character Set:
“Unicode”; Field Mapping: Source field 1 match with setupReference::_LlibrarySetupHowToCredit
Source field 2 import to setupReference::_Number
Source field 3 import to setupReference::URL
Source field 4 import to setupReference::publicationDate
Source field 5 import to setupReference::kcreatorNode
Source field 6 import to setupReference::name
Source field 7 import to setupReference::password
Source field 8 import to setupReference::klibrary
Source field 9 import to setupReference::version
Source field 13 import to setupReference::creatorName
Source field 14 import to setupReference::note ]
[ No dialog ]
End If
#
#
#5) Import tag records.
Go to Layout [ “tableTag” (tagTable) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “tagTable”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1
import to tagTable::kGroupOrTest
Source field 2 import to tagTable::_Ltag
Source field 3 import to tagTable::tag
Source field 4 import to tagTable::orderOrLock
Source field 5 import to tagTable::textStyleOrCreatorNodeFlag
Source field 6 import to tagTable::_Number
Source field 7 import to tagTable::match
Source field 8 import to tagTable::tagSpelling
Source field 9 import to tagTable::Kpicture1
Source field 10 import to tagTable::notesOrCopyright
Source field 11 import to tagTable::Ktitle1
Source field 12 import to tagTable::kfileORkTestItemCreatorNode
Source field 14 import to tagTable::Kpicture2
Source field 16 import to tagTable::Kpicture3
Source field 18 import to tagTable::Ktitle2
Source field 19 import to tagTable::Ktitle3
Source field 23 import to tagTable::kRecordCreatorNode
Source field 24 import to tagTable::notesForKeyandNodeTags ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “tagTable”; Method: Update matching; Add remaining; Character Set: “Unicode”;
Field Mapping: Source field 1 import to tagTable::kGroupOrTest
Source field 2 match with tagTable::_Ltag
Source field 3 import to tagTable::tag
Source field 4 import to tagTable::orderOrLock
Source field 5 import to tagTable::textStyleOrCreatorNodeFlag
Source field 6 import to tagTable::_Number
Source field 7 import to tagTable::match
Source field 8 import to tagTable::tagSpelling
Source field 9 import to tagTable::Kpicture1
Source field 10 import to tagTable::notesOrCopyright
Source field 11 import to tagTable::Ktitle1
Source field 12 import to tagTable::kfileORkTestItemCreatorNode
Source field 14 import to tagTable::Kpicture2
Source field 16 import to tagTable::Kpicture3
Source field 18 import to tagTable::Ktitle2
Source field 19 import to tagTable::Ktitle3
Source field 23 import to tagTable::kRecordCreatorNode
Source field 24 import to tagTable::notesForKeyandNodeTags ]
[ No dialog ]
End If
#
#Update primary node just in case it was
#changed by the import.
If [ TEMP::kdefaultNodePrimary ≠ "" ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; TEMP::kdefaultNodePrimary ]
Perform Find [ ]
If [ tagTable::_Ltag = TEMP::kdefaultNodePrimary ]
Set Field [ TEMP::DEFAULTNodePrimaryName; tagTable::tag ]
End If
End If
#
#Update test subject node just in case it was
#changed by the import.
If [ TEMP::kdefaultNodeTestSubject ≠ "" ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
If [ tagTable::_Ltag = TEMP::kdefaultNodeTestSubject ]
Set Field [ TEMP::DEFAULTNodeTestSubjectName; tagTable::tag ]
End If
End If
#
#
#6) Import tag group records.
#
#Get this library's ID and name. It will be
#checked for changes after import.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “testSubsectionGroup”; Method: Add; Character Set: “Unicode”; Field Mapping:
Source field 1 import to testSubsectionGroup::_Lgroup
Source field 2 import to testSubsectionGroup::_Number
Source field 3 import to testSubsectionGroup::match
Source field 4 import to testSubsectionGroup::name
Source field 5 import to testSubsectionGroup::klibrary
Source field 6 import to testSubsectionGroup::nameSpellingFORTestItemGroup
Source field 7 import to testSubsectionGroup::testReportPicture
Source field 8 import to testSubsectionGroup::ReportCaptionORLibraryCreatorName
Source field 9 import to testSubsectionGroup::URLOrCopyrightORUserLibraryVersion
Source field 10 import to testSubsectionGroup::orderOrLibraryType
Source field 11 import to testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup
Source field 12 import to testSubsectionGroup::kRecordCreatorNode
Source field 13 import to testSubsectionGroup::versionNumber ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “testSubsectionGroup”; Method: Update matching; Add remaining; Character Set:
“Unicode”; Field Mapping: Source field 1 match with testSubsectionGroup::_Lgroup
Source field 2 import to testSubsectionGroup::_Number
Source field 3 import to testSubsectionGroup::match
Source field 4 import to testSubsectionGroup::name
Source field 5 import to testSubsectionGroup::klibrary
Source field 6 import to testSubsectionGroup::nameSpellingFORTestItemGroup
Source field 7 import to testSubsectionGroup::testReportPicture
Source field 8 import to testSubsectionGroup::ReportCaptionORLibraryCreatorName
Source field 9 import to testSubsectionGroup::URLOrCopyrightORUserLibraryVersion
Source field 10 import to testSubsectionGroup::orderOrLibraryType
Source field 11 import to testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup
Source field 12 import to testSubsectionGroup::kRecordCreatorNode
Source field 13 import to testSubsectionGroup::versionNumber ]
[ No dialog ]
End If
#
#Remove imported library's libraryID record.
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::match: “"library"” ]
[ Restore ]
Go to Record/Request/Page
[ First ]
Loop
#
If [ testSubsectionGroup::_Lgroup ≠ $libraryID ]
Set Field [ testSubsectionGroup::orderOrLibraryType; "lock" ]
Set Field [ testSubsectionGroup::match; "libraryIMPORTED" ]
End If
#
#Check if the name of this library
#was changed.
If [ testSubsectionGroup::_Lgroup = $libraryID ]
If [ testSubsectionGroup::name ≠ $$libraryNameForNameChangeCheck ]
Set Variable [ $$libraryNameWASChanged; Value:testSubsectionGroup::name ]
Set Field [ TEMP::userLibraryName; testSubsectionGroup::name ]
End If
End If
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#
#7) Import reference records.
Go to Layout [ “tableReference” (reference) ]
Show All Records
#
#Omit locked copyright records. This is
#important to insure that the copyright records
#being imported, perhaps from an older version
#do not overwrite this library's copyright records.
If [ Get (FoundCount) ≠ 0 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::lock; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
If [ reference::lock = "lock" ]
Omit Record
End If
Exit Loop If [ reference::lock ≠ "lock" ]
Exit Loop If [ Get (FoundCount) = 0 ]
End Loop
End If
#
#Perform import.
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “reference”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1
import to reference::_Number
Source field 2 import to reference::_Lreference
Source field 3 import to reference::ktestSubject
Source field 4 import to reference::ktest
Source field 5 import to reference::kclibrary
Source field 6 import to reference::knodePrimary
Source field 7 import to reference::publicationYearOrStuffOrderNumber
Source field 8 import to reference::URL
Source field 9 import to reference::URLdate
Source field 10 import to reference::Title
Source field 11 import to reference::kpublication
Source field 12 import to reference::volumeNumber
Source field 13 import to reference::PubDate
Source field 14 import to reference::pageNumberRange
Source field 15 import to reference::kpublisher
Source field 16 import to reference::OrginalCitation
Source field 17 import to reference::kcopyrightType
Source field 18 import to reference::kCopyright
Source field 19 import to reference::kmedium
Source field 20 import to reference::kkeywordOther
Source field 21 import to reference::kkeywordPrimary
Source field 22 import to reference::thoughtsNotesEtc
Source field 23 import to reference::kfolderpath
Source field 24 import to reference::fileName
Source field 26 import to reference::referenceNodes
Source field 27 import to reference::CopyrightYear
Source field 28 import to reference::kcopyrightHolder
Source field 29 import to reference::referenceDump
Source field 30 import to reference::knodeOther
Source field 31 import to reference::NodeOthers
Source field 32 import to reference::OtherKeyWords
Source field 33 import to reference::referenceNodesOLD
Source field 34 import to reference::filterFind
Source field 35 import to reference::picture
Source field 36 import to reference::kfileLocation
Source field 37 import to reference::rights
Source field 38 import to reference::mFileFolderMainXorOther
Source field 39 import to reference::kcitation
Source field 40 import to reference::incomplete
Source field 41 import to reference::lock
Source field 43 import to reference::kcreatorNode
Source field 44 import to reference::kmodifierNode
Source field 45 import to reference::modifyDate
Source field 47 import to reference::TimeRange
Source field 48 import to reference::createDate
Source field 49 import to reference::showInLearn
Source field 50 import to reference::publicLibraryLinks
Source field 51 import to reference::DOI
Source field 52 import to reference::issueNumber
Source field 53 import to reference::publisherLocation
Source field 54 import to reference::publicationTitle
Source field 55 import to reference::compilationEditors
Source field 56 import to reference::kisWhat
Source field 57 import to reference::kisON
Source field 58 import to reference::compilationNumberOfEditors
Source field 59 import to reference::publicationYearMonthRange
Source field 60 import to reference::ISBN
Source field 61 import to reference::pubDateOther
Source field 62 import to reference::bookChapter
Source field 63 import to reference::letterDate
Source field 64 import to reference::compilationAbbr
Source field 65 import to reference::emailRecipient
Source field 66 import to reference::conferenceIntroWords
Source field 67 import to reference::conferenceTitle
Source field 68 import to reference::conferenceSubTitle
Source field 69 import to reference::conferenceLocation
Source field 70 import to reference::conferenceDate
Source field 71 import to reference::otherIsOn
Source field 72 import to reference::GovernmentDocInfo
Source field 73 import to reference::governmentAuthor
Source field 74 import to reference::ISSN
Source field 75 import to reference::publisherTypeAlternative
Source field 76 import to reference::copyrightOtherHolder
Source field 77 import to reference::publisherTypeOther
Source field 78 import to reference::pageNumberOther
Source field 79 import to reference::dissertationThesisUniversity
Source field 83 import to reference::showMedia
Source field 84 import to reference::showMediaCode
Source field 85 import to reference::PictureFileSize
Source field 87 import to reference::pictureSourceSpeedLimit
Source field 88 import to reference::pictureThumbnail
Source field 91 import to reference::otherIsWhat ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “reference”; Method: Update matching; Add remaining; Character Set: “Unicode”;
Field Mapping: Source field 1 import to reference::_Number
Source field 2 match with reference::_Lreference
Source field 3 import to reference::ktestSubject
Source field 4 import to reference::ktest
Source field 5 import to reference::kclibrary
Source field 6 import to reference::knodePrimary
Source field 7 import to reference::publicationYearOrStuffOrderNumber
Source field 8 import to reference::URL
Source field 9 import to reference::URLdate
Source field 10 import to reference::Title
Source field 11 import to reference::kpublication
Source field 12 import to reference::volumeNumber
Source field 13 import to reference::PubDate
Source field 14 import to reference::pageNumberRange
Source field 15 import to reference::kpublisher
Source field 16 import to reference::OrginalCitation
Source field 17 import to reference::kcopyrightType
Source field 18 import to reference::kCopyright
Source field 19 import to reference::kmedium
Source field 20 import to reference::kkeywordOther
Source field 21 import to reference::kkeywordPrimary
Source field 22 import to reference::thoughtsNotesEtc
Source field 23 import to reference::kfolderpath
Source field 24 import to reference::fileName
Source field 26 import to reference::referenceNodes
Source field 27 import to reference::CopyrightYear
Source field 28 import to reference::kcopyrightHolder
Source field 29 import to reference::referenceDump
Source field 30 import to reference::knodeOther
Source field 31 import to reference::NodeOthers
Source field 32 import to reference::OtherKeyWords
Source field 33 import to reference::referenceNodesOLD
Source field 34 import to reference::filterFind
Source field 35 import to reference::picture
Source field 36 import to reference::kfileLocation
Source field 37 import to reference::rights
Source field 38 import to reference::mFileFolderMainXorOther
Source field 39 import to reference::kcitation
Source field 40 import to reference::incomplete
Source field 41 import to reference::lock
Source field 43 import to reference::kcreatorNode
Source field 44 import to reference::kmodifierNode
Source field 45 import to reference::modifyDate
Source field 47 import to reference::TimeRange
Source field 48 import to reference::createDate
Source field 49 import to reference::showInLearn
Source field 50 import to reference::publicLibraryLinks
Source field 51 import to reference::DOI
Source field 52 import to reference::issueNumber
Source field 53 import to reference::publisherLocation
Source field 54 import to reference::publicationTitle
Source field 55 import to reference::compilationEditors
Source field 56 import to reference::kisWhat
Source field 57 import to reference::kisON
Source field 58 import to reference::compilationNumberOfEditors
Source field 59 import to reference::publicationYearMonthRange
Source field 60 import to reference::ISBN
Source field 61 import to reference::pubDateOther
Source field 62 import to reference::bookChapter
Source field 63 import to reference::letterDate
Source field 64 import to reference::compilationAbbr
Source field 65 import to reference::emailRecipient
Source field 66 import to reference::conferenceIntroWords
Source field 67 import to reference::conferenceTitle
Source field 68 import to reference::conferenceSubTitle
Source field 69 import to reference::conferenceLocation
Source field 70 import to reference::conferenceDate
Source field 71 import to reference::otherIsOn
Source field 72 import to reference::GovernmentDocInfo
Source field 73 import to reference::governmentAuthor
Source field 74 import to reference::ISSN
Source field 75 import to reference::publisherTypeAlternative
Source field 76 import to reference::copyrightOtherHolder
Source field 77 import to reference::publisherTypeOther
Source field 78 import to reference::pageNumberOther
Source field 79 import to reference::dissertationThesisUniversity
Source field 83 import to reference::showMedia
Source field 84 import to reference::showMediaCode
Source field 85 import to reference::PictureFileSize
Source field 87 import to reference::pictureSourceSpeedLimit
Source field 88 import to reference::pictureThumbnail
Source field 91 import to reference::otherIsWhat ]
[ No dialog ]
End If
#
#Now delete the imported lock copyright
#records, to insure the latests locked
#copyright records already in this file remain
#the only ones.
If [ Get (FoundCount) ≠ 0 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::lock; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
If [ reference::lock = "lock" ]
Delete Record/Request
[ No dialog ]
End If
Exit Loop If [ reference::lock ≠ "lock" ]
Exit Loop If [ Get (FoundCount) = 0 ]
End Loop
End If
#
#
#8) Import report records.
Go to Layout [ “tableReport” (report) ]
Show All Records
If [ Get (FoundCount) = 0 ]
Import Records [ Source: “$filepath”; Target: “report”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1
import to report::_Lreport
Source field 2 import to report::_Number
Source field 3 import to report::ktestSubject
Source field 4 import to report::kTestSubjectSection
Source field 5 import to report::general_info
Source field 6 import to report::ktestSubsection
Source field 7 import to report::kRecommendation1
Source field 8 import to report::order
Source field 9 import to report::Picture
Source field 10 import to report::kRecommendation2
Source field 11 import to report::kgeneralSpecificItemRecommendationID
Source field 12 import to report::kTag1
Source field 13 import to report::kTestSubjectSection2
Source field 14 import to report::kTestSubjectSection3
Source field 15 import to report::kTestSubjectSection4
Source field 16 import to report::kTestSubjectSection5
Source field 17 import to report::PictureCaptionInsteadOfPicture
Source field 18 import to report::note
Source field 19 import to report::textPhotoRow1
Source field 20 import to report::pagenumberItem
Source field 21 import to report::CurrentRecord
Source field 22 import to report::kTag2
Source field 23 import to report::kTag3
Source field 24 import to report::kTag4
Source field 25 import to report::pagenumberTheme
Source field 26 import to report::TOC
Source field 27 import to report::TOCnumbers
Source field 28 import to report::ReportCover
Source field 29 import to report::ReportPDFtitle
Source field 30 import to report::kreportNumber
Source field 31 import to report::klibrary
Source field 32 import to report::kRecordCreatorNode
Source field 33 import to report::kRecordModifierNode
Source field 34 import to report::RecordModifyDate
Source field 35 import to report::kcopyright
Source field 36 import to report::textPhotoRow2 ]
[ No dialog ]
Else
Import Records [ Source: “$filepath”; Target: “report”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field
Mapping: Source field 1 match with report::_Lreport
Source field 2 import to report::_Number
Source field 3 import to report::ktestSubject
Source field 4 import to report::kTestSubjectSection
Source field 5 import to report::general_info
Source field 6 import to report::ktestSubsection
Source field 7 import to report::kRecommendation1
Source field 8 import to report::order
Source field 9 import to report::Picture
Source field 10 import to report::kRecommendation2
Source field 11 import to report::kgeneralSpecificItemRecommendationID
Source field 12 import to report::kTag1
Source field 13 import to report::kTestSubjectSection2
Source field 14 import to report::kTestSubjectSection3
Source field 15 import to report::kTestSubjectSection4
Source field 16 import to report::kTestSubjectSection5
Source field 17 import to report::PictureCaptionInsteadOfPicture
Source field 18 import to report::note
Source field 19 import to report::textPhotoRow1
Source field 20 import to report::pagenumberItem
Source field 21 import to report::CurrentRecord
Source field 22 import to report::kTag2
Source field 23 import to report::kTag3
Source field 24 import to report::kTag4
Source field 25 import to report::pagenumberTheme
Source field 26 import to report::TOC
Source field 27 import to report::TOCnumbers
Source field 28 import to report::ReportCover
Source field 29 import to report::ReportPDFtitle
Source field 30 import to report::kreportNumber
Source field 31 import to report::klibrary
Source field 32 import to report::kRecordCreatorNode
Source field 33 import to report::kRecordModifierNode
Source field 34 import to report::RecordModifyDate
Source field 35 import to report::kcopyright
Source field 36 import to report::textPhotoRow2 ]
[ No dialog ]
End If
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
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
#
#Restart database to insure updated file's
#information are used for this library's temp
#fields and variables.
Show Custom Dialog [ Message: "Library will now restart to reset values that could have changed due to changes made during
import." ]
Perform Script [ “startDatabase” ]
#
#
