tagMenu: menuTest
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear sample and test tags.
If [ $$citationMatch = "sample" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Field [ TEMP::ktest; "" ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#Clear order numbers.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 1; Width: 1 ]
Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testlearn::orderTest: “###” ]
[ Restore ]
Loop
Set Field [ testlearn::orderTest; "" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Close Window [ Current Window ]
Set Variable [ $$stopLoadTagRecord ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"test" ]
#
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnTest” (test) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnTest” (test) ]
End If
#
#Find section tags. Test tags are library
#items. Any brainstorm or evidence record
#can be tagged with any section item record SO
#find all library sections current record is
#assigned to.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ test::ksection; TEMP::ksection ]
Perform Find [ ]
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
#
If [ TEMP::sortTest = "cat" or TEMP::sortTest = "" ]
Sort Records [ Specified Sort Order: groupTest::order; based on value list: “order”
groupTest::name; ascending
tagMenus::orderOrLock; based on value list: “order”
test::order; ascending
test::testName; ascending ]
[ Restore; No dialog ]
Else If [ $$citationMatch = "test" ]
Set Field [ TEMP::sortTest; "abc" ]
End If
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" = test::_Ltest & ¶ ]
Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" = test::_Ltest & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" ≠ test::_Ltest & ¶ ]
Go to Record/Request/Page
[ First ]
End If
#
#Turn loadtagrecord script back on and perform
#loadtag... script to highlight any Learn records
#tagged with the current tag record.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadItemRecordForTestTagMenu” ]
#
January 7, 平成26 15:59:01 Imagination Quality Management.fp7 - menuTest -1-
