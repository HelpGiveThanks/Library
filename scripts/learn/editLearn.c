learn: editLearn
#
#In report mode do the following ...
If [ Left ( Get ( LayoutName ) ; 1 ) = "r" ]
#
#Set return variable for tag.
If [ Get (FoundCount) ≥ 1 ]
Set Variable [ $$learnRecord; Value:testlearnReportTags::_Ltestlearn ]
Else
Set Variable [ $$learnRecord; Value:1 ]
End If
#
#Set return variable for Report item.
Set Variable [ $$returnItem; Value:TEMP::ktest ]
Set Variable [ $$returnItemName; Value:TEMP::testName ]
#
#Go to the Report window and change it to Learn.
Select Window [ Name: "Report"; Current file ]
Set Window Title [ Current Window; New Title: "Learn" ]
#
#Find, sort, the loop to record user was on in
#Tag Menus window for info items (testLearn records).
Set Variable [ $$stopLoadCitation; Value:1 ]
If [ tempSetup::layoutLmain = "" ]
Go to Layout [ “learn1” (testlearn) ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
Go to Layout [ Middle ( tempSetup::layoutLmain ; 5 ; 42 ) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Go to selected learn record if there is one.
Go to Record/Request/Page
[ First ]
If [ $$learnRecord ≠ "" ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$learnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Go to test menu in Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$editTestInfo; Value:1 ]
Perform Script [ “menuTest (update)” ]
#
#
#
#
#
#In test mode do the following ...
Else If [ Left ( Get ( LayoutName ) ; 1 ) = "t" ]
#
#Set return variable for tag.
Set Variable [ $$testTagRecord; Value:testlearnReportTags::_Ltestlearn ]
If [ $$testTagRecord = "" ]
Set Variable [ $$testTagRecord; Value:"blank" ]
End If
#
#Set return variable for Test item.
Set Variable [ $$returnItem; Value:TEMP::ktest ]
Set Variable [ $$returnItemName; Value:TEMP::testName ]
#
#Go to the Test window and change it to Learn.
Select Window [ Name: "Test"; Current file ]
Set Window Title [ Current Window; New Title: "Learn" ]
#
#Set return variable for main Test record.
Set Variable [ $$testLearnRecord; Value:testlearn::_Ltestlearn ]
#
#Find, sort, the loop to record user was on in
#Tag Menus window for info items (testLearn records).
Set Variable [ $$stopLoadCitation; Value:1 ]
If [ tempSetup::layoutLmain = "" ]
Go to Layout [ “learn1” (testlearn) ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
Go to Layout [ Middle ( tempSetup::layoutLmain ; 5 ; 42 ) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Go to selected learn record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$testTagRecord or $$testTagRecord = "blank" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stopLoadCitation ]
#
#Go to test menu in Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$editTestInfo; Value:1 ]
Perform Script [ “menuTest (update)” ]
End If
#
December 27, ଘ౮27 21:57:45 Library.fp7 - editLearn -1-
