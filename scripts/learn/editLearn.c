January 16, 2018 15:41:30 Library.fmp12 - editLearn -1-
learn: editLearn
#
#
#This script is activated on Test Info layouts,
#and functions to take user to the learn
#module where they can edit info records
#assigned to the test subsection they are
#viewing.
#
#
#
#
#
#BEGIN: Stop this script if any of the following are true:
#
#Test subject is locked.
#
#NOTE: Although changing associated learn
#and test item records cannot affect a test
#subjects test result or report records, further
#testing and so time is required to insure no
#problems occur as a result of allowing users to
#edit learn and test subsection records when
#navigating from locked Test Section item and
#info Tag Menus layouts.
If [ $$testSubjectIsLocked ≠ "" and Get ( LayoutName ) ≠ "defaultTest" and Get ( LayoutName ) ≠ "learnTest" ]
Show Custom Dialog [ Message: "The test subject — " & $$testSubjectIsLocked & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“No” ]
Set Variable [ $exit; Value:1 ]
End If
#
#Primary node is locked.
If [ TEMP::primaryNodeIsLocked ≠ "" ]
If [ $exit = "" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked.
Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C)
create a new primary node."; Default Button: “OK”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "ALSO, the default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is
locked. Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary
node, or C) create a new primary node."; Default Button: “OK”, Commit: “No” ]
End If
Set Variable [ $exit; Value:1 ]
End If
#
#Subsection is locked by its creator node.
If [ $$testSubsectionIsLocked ≠ "" and Get ( LayoutName ) ≠ "defaultTest"
 or
testSectionCreatorLock::orderOrLock ≠ "" and Get ( LayoutName ) ≠ "defaultTest" ]
#
If [ $exit = "" ]
If [ Left (Get (LayoutName) ; 5 ) = "learn" ]
Show Custom Dialog [ Message: "This test subsection's creator node — " & testSectionCreatorLock::tag & " — is
locked. Go to the Default Node Tag Menu and click 'lock' to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "You cannot add or subtract any info records as this subsection is locked by its
creator — " & $$testSubsectionIsLocked & ". If you know this node's password, you can unlock it on the Setup
section's node menu."; Default Button: “OK”, Commit: “Yes” ]
End If
Set Variable [ $exit; Value:1 ]
End If
#
End If
#
#If any of the above are true, then
#exit this script.
If [ $exit = 1 ]
Exit Script [ ]
End If
#
#
#END: Stop this script if any of the following are true:
#
#
#
#
#
#Go the Learn module be first closing the
#Reference window and resizing the two
#remaining windows.
Close Window [ Name: "Reference"; Current file ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2 ]
Select Window [ Name: "Tag Menus"; Current file ]
#
#Because of the complexity of going to learn
#module from the test module, this variable
#needs to be set to stop a reference window
#from being opened. Probably there is a better
#way to accomplish this, but more testing is
#required to figure the more efficient path.
Set Variable [ $$doNotOpenReferenceWindow; Value:1 ]
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
Set Variable [ $$returnItem; Value:TEMP::ktestSubsection ]
Set Variable [ $$returnItemName; Value:TEMP::testSubsectionName ]
#
#Go to the Report window and change it to Learn.
Select Window [ Name: "Report"; Current file ]
Set Window Title [ Current Window; New Title: "Learn" ]
#
#Find, sort, the loop to record user was on in
#Tag Menus window for info items (testLearn records).
Set Variable [ $$stopLoadCitation; Value:1 ]
If [ tempSetup::layoutLmain = "" ]
Go to Layout [ “learn2” (testlearn) ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
Go to Layout [ Middle ( tempSetup::layoutLmain ; 5 ; 42 ) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Go to selected learn record if there is one.
If [ $$thereIsInfoForThisSubsection = 1 ]
If [ $$learnRecord ≠ "" ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$learnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
End If
Set Variable [ $$stopLoadCitation ]
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
Set Variable [ $$returnItem; Value:TEMP::ktestSubsection ]
Set Variable [ $$returnItemName; Value:TEMP::testSubsectionName ]
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
Go to Layout [ “learn2” (testlearn) ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
Go to Layout [ Middle ( tempSetup::layoutLmain ; 5 ; 42 ) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Go to selected learn record, if there is one.
If [ $$thereIsInfoForThisSubsection = 1 ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$testTagRecord or $$testTagRecord = "blank" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Set Variable [ $$stopLoadCitation ]
#
#Go to test menu in Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$editTestInfo; Value:1 ]
Perform Script [ “menuTest (update)” ]
End If
#
