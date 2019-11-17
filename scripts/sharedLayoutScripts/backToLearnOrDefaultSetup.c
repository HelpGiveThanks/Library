October 31, 2019 17:57:11 Library.fmp12 - -1-
backToLearnOrDefaultSetup
sharedLayoutScripts: backToLearnOrDefaultSetup
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Set Variable [ $$referenceRecordOne ]
Set Variable [ $$referenceSort ]
Set Variable [ $$findMode ]
#
#
#If in stuff library mode, run these next steps to
#replace any dragged changes to stuff
#reference/location records. This is where the
#user did not enter a record's field to change
#them, but instead just dragged (maybe
#accidentally) text into fields. If so, the script
#that updates the backup field or, when the
#record is locked, replaces changes with the
#backup data, is not triggered, SO this next bit
#of script takes care of dragged changes.
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
#
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “tableReference” (reference) ]
Set Variable [ $$stoploadCitation ]
#
#
Go to Record/Request/Page
[ First ]
Loop
#
#
#If the record is unlocked, then save any
#changes in the backup data fields.
If [ refCreatorNode::orderOrLock = "" ]
#
#Only change records that have been changed.
#Changes result in the record modify date being
#reset, and this should only be done when the
#user modifies the record.
If [ reference::Title[1] ≠ reference::Title[2] ]
Set Field [ reference::Title[2]; reference::Title[1] ]
End If
If [ reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2] ]
Set Field [ reference::thoughtsNotesEtc[2]; reference::thoughtsNotesEtc[1] ]
End If
If [ reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2] ]
#
#Insure that only 3 digit numbers are
#saved in this field.
Set Variable [ $threeDigitNumber; Value:Right ( GetAsNumber (reference::publicationYearOrStuffOrderNumber
[1]) ; 3 ) ]
Set Field [ reference::publicationYearOrStuffOrderNumber[2]; $threeDigitNumber ]
Set Field [ reference::publicationYearOrStuffOrderNumber; $threeDigitNumber ]
End If
#
#
#If the record is locked, then replace any
#changes with the saved back up data.
Else If [ refCreatorNode::orderOrLock ≠ "" ]
#
#
#Only change records that have been changed.
#Changes result in the record modify date being
#reset, and this should only be done when the
#user modifies the record.
If [ reference::Title[1] ≠ reference::Title[2] ]
Set Field [ reference::Title; reference::Title[2] ]
End If
If [ reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2] ]
Set Field [ reference::thoughtsNotesEtc; reference::thoughtsNotesEtc[2] ]
End If
If [ reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2] ]
Set Field [ reference::publicationYearOrStuffOrderNumber; reference::publicationYearOrStuffOrderNumber[2] ]
End If
#
End If
#
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#
End If
#
#
#Clear main record node lock variable.
Set Variable [ $$lockedMainRefRecord ]
#
#Set in copyAndpastTags script.
Set Variable [ $$copyAndpastTagsRECORD ]
#
If [ Left ( $$defaultTagLayout ; 1 ) = "d" ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
#
#Check for any dragged changes to tag spellings.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Show All Records
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “CHUNK_checkForDraggedPasteChanges” ]
#
#Go to default tags layout
#and load up defaults.
Perform Script [ “defaultsAll” ]
Set Variable [ $$stopAddTagToCitation ]
Set Variable [ $$defaultRecordNumber ]
Set Variable [ $$defaultTagLayout ]
Set Variable [ $$citationMatch ]
#
#Change main window to Setup.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Set Window Title [ Current Window; New Title: "Setup" ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
#
#Clear variables that where set
#in other modules.
Go to Field [ ]
Set Variable [ $$citationitem; Value:tempSetup::klibrary ]
Set Variable [ $$stopAddTagToCitation ]
Set Variable [ $$defaultRecordNumber ]
Set Variable [ $$defaultTagLayout ]
Set Variable [ $$node ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagTest ]
Set Variable [ $$citationRecord ]
Set Variable [ $$primaryNode ]
Set Variable [ $$medium ]
Set Variable [ $$copyright ]
Set Variable [ $$Path ]
Set Variable [ $$cite ]
Set Variable [ $$ref ]
Set Variable [ $$PrimaryKey ]
Set Variable [ $$Key ]
Set Variable [ $$OtherKey ]
Set Variable [ $$RecordID ]
#
Set Field [ TEMP::ktestSubsection; "" ]
#
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Set Variable [ $$findLayout ]
Exit Script [ ]
End If
#
#Go to testlearn layout and loop back to record.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Window Title [ Current Window; New Title: "Learn" ]
#
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn2” (testlearn) ]
Else
Go to Layout [ “learnStuff2” (testlearn) ]
End If
#
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
#
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$LearnEdit = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Show user layout that they selected.
If [ tempSetup::layoutLmain = "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn2” (testlearn) ]
Else
Go to Layout [ “learnStuff3” (testlearn) ]
End If
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ "Learn" & Right ( tempSetup::layoutLmain ; 1 ) ]
Else
Go to Layout [ "LearnStuff" & Right ( tempSetup::layoutLmain ; 1 ) ]
End If
End If
#
Set Variable [ $$stoploadCitation ]
#
#Go to Learn tag menu layout and loop back to record.
Select Window [ Name: "Tag Menus"; Current file ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
#
#Check for any dragged changes to tag spellings.
Go to Field [ ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Show All Records
Set Variable [ $$stopLoadTagRecord ]
#
#Prevent halting to loadTagRecord script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
Perform Script [ “CHUNK_checkForDraggedPasteChanges” ]
#
Go to Layout [ $$learnTagLayout ]
Set Variable [ $$learnTagLayout ]
Set Variable [ $$stopLoadTagRecord ]
If [ $$module = "ref" ]
Perform Script [ “menuReference” ]
Else If [ $$module = "learnTest"
 or
$$module = "learnSTest" ]
Perform Script [ “menuTest” ]
End If
#
#Turn of stop halt variable.
Set Variable [ $$doNotHaltOtherScripts ]
#
Select Window [ Name: "Learn"; Current file ]
#
#Perform Load Citation script to restore conditional
#formatting.
Perform Script [ “loadLearnOrRefMainRecord” ]
#
#Finish up back script on the Tag Menus
#if this is where the user started from by
#clicking an edit/new button.
If [ $$module = "ref" or $$module = "learnTest" ]
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#
#If there is only one node and it is the
#Admin node, the inform the user that they
#need to make a node for themselves.
If [ $$AdminOnlyNode = 1 and Get ( AccountName ) ≠ "Admin" ]
Show Custom Dialog [ Message: "NOTE: Log in as the Admin user if do not want to see these messages about creating a unique
node for yourself."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Create a node/author record for yourself in the SetUp Section, so that you will have a unique
ID associated with all the records that you create."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "This is not the Setup Section."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "1) Click back until you reach the Setup Section. 2) go to the Tag Menu window. 2) Click the
node button."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "3) Click the P button next to your name to select yourself as the creator of all new library
records."; Default Button: “OK”, Commit: “Yes” ]
Else
Set Variable [ $$AdminOnlyNode ]
End If
#
#
