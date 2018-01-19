January 15, 2018 16:25:08 Library.fmp12 - menuTest -1-
tagMenu: menuTest
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Prevent halting of script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear brainstorm and test tags.
If [ $$citationMatch = "brainstorm" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Field [ TEMP::ktestSubsection; "" ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#Clear testlearn records' order numbers.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 1; Width: 1; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testlearn::orderTestInformation: “###” ]
[ Restore ]
Loop
Set Field [ testlearn::orderTestInformation; "" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Close Window [ Current Window ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#Conditionally format Tag Menu button.
Set Variable [ $$citationMatch; Value:"test" ]
#
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnTest” (testSubsectionTemplate) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnSTest” (testSubsectionTemplate) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnTest” (testSubsectionTemplate) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnSTest” (testSubsectionTemplate) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "t" ]
Go to Layout [ “learnTest” (testSubsectionTemplate) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnSTest” (testSubsectionTemplate) ]
End If
End If
#
#Find test subsection tags.
If [ $$testSubsection = "" ]
Show All Records
Else
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::_LtestSubsection; $$testSubsection ]
Perform Find [ ]
Show Custom Dialog [ Message: "Learn records can ONLY be added and removed from the subsection being edited. To edit
ALL subsections' info, 1) click the back buttons until you return to Library Setup. 2) Click Learn, and 3) in the Tag Menus
window, click test."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#Sort into groups.
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
testSubsectionGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
testSubsectionTemplate::order; ascending
testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
#
#If user did not just come from the test
#module, go to current learn record's first
#listed test or the first test record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
If [ $$editTestInfo ≠ 1 ]
Loop
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" = testSubsectionTemplate::_LtestSubsection & ¶ ]
Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" = testSubsectionTemplate::_LtestSubsection & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" ≠ testSubsectionTemplate::_LtestSubsection & ¶ ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
End If
#
#If user just came from test module then loop
#to the test the user was interested in editing.
Else
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$testSubsection = testSubsectionTemplate::_LtestSubsection ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Turn loadtagrecord script back on and perform
#load-test-tag script to highlight any Learn records
#tagged with the current tag record.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTestTags (update and name change from loadItemRecordForTestTagMenu)” ]
#
