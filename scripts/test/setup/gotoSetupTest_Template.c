January 11, 2018 19:59:26 Library.fmp12 - gotoSetupTest_Template -1-
test: setup: gotoSetupTest_Template
#
#
#Prevent user from going to the edit test
#template section, when user has come here
#from a Test or Report window. The scripts do
#work to allow this, but it gives the user too
#many options, and they can lose focus on
#editing the current subsection's info, which is
#why they have come here when the come from
#the Report or Test windows.
# Taking away this option here is just an
#inconvenience, as the user can return to the
#Setup Section and edit test templates.
# The user is still allowed to go edit
#templates from the Learn Section, when their
#work is focused in the Learn Section versus
#focused in the Test Section, and they have
#just briefly come to the Learn Section to make
#some quick edits, before returning the
#Test Section.
If [ ( $$testTagRecord = "" and $$learnRecord = "" ) = 0 ]
// Show Custom Dialog [ Message: "Going to the test-template edit-section of the library is not allowed when coming here from
Test or Report sections. Click the back buttons until you return to Library Setup. Then from Setup, go to the Test Template
edit section."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#
#
#
#BEGIN: Stop this script if any of the following are true:
#
#If there are no test sections to go to from
#the learn layout.
If [ Left (Get (LayoutName) ; 5 ) = "learn"
and
Get (FoundCount) = 0 ]
Exit Script [ ]
End If
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
Show Custom Dialog [ Message:
"This test subsection's creator node — " & testSectionCreatorLock::tag & " — is locked. Go to the Default Node
Tag Menu and click 'lock' to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "You can use all of this subsection's test items, but not edit them as this subsection is
locked by its creator — " & $$testSubsectionIsLocked & ". If you know this node's password, you can unlock it on
the Setup section's node menu."; Default Button: “OK”, Commit: “Yes” ]
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
#Make sure script is starting in the
#Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#Clear citation match variable as effects the
#exit field scripts in the test section.
Set Variable [ $$citationMatch ]
#
#Stop the spell checking script to
#speed things up.
Set Variable [ $$stopTest; Value:1 ]
#
#Capture record ID so system can return user
#after editing is complete.
Set Variable [ $$recordNumber; Value:Get (RecordNumber) ]
#
#Capture test and test item IDs so system can
#reset them. During edit user may go to a
#different test record, thus changing these temp IDs.
If [ Get (LayoutName) = "learnTest" ]
Set Variable [ $$itemID; Value:testSubsectionTemplate::_LtestSubsection ]
Else
Set Variable [ $$itemID; Value:TEMP::ktestSubsection ]
End If
Set Variable [ $$detailID; Value:TEMP::ktestItemSubsection ]
#
#Capture layoutname so system can return user
#after editing is complete.
Set Variable [ $$module; Value:Get (LayoutName) ]
#
#Go to section tag menu so section script
#steps below will work properly.
Go to Layout [ “setupTestSection” (testSection) ]
#
#If coming from the library's Test Setup layout,
#show user the library's test sections.
If [ Left ( $$module ; 7 ) = "default" ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
View As
[ View as List ]
Enter Find Mode [ ]
Set Field [ testSection::match; "testSection" ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSection::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
End If
#
#
#
#Capture record ID so system can return user
#after editing is complete.
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Test"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Report"; Current file ]
End If
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$LearnEdit; Value:testlearn::_Ltestlearn ]
End If
#
#
If [ Get (WindowName) ≠ "Setup" ]
Set Variable [ $editingOneSubsection; Value:1 ]
End If
#
#Take user to test setup layout and find all
#test subsection templates. If coming from
#Library Setup window, if coming from a Test
#Tag Menus window or Report Tag Menus
#window, then only find the one subsection
#showing in that Tag Menus window.
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “setupTestSubsection” (testSubsectionTemplate) ]
Set Window Title [ Current Window; New Title: "Test Templates" ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ $editingOneSubsection ≠ 1 ]
Show All Records
Else
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::_LtestSubsection; $$itemID ]
Perform Find [ ]
End If
#
#If no test exist, then make sure Tag Menus
#also shows no section templates.
If [ Get (LastError) = 401 ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Find [ Specified Find Requests: Find Records; Criteria: tagMenus::_Ltag: “"findNOrecords"” ]
[ Restore ]
Select Window [ Name: "Setup"; Current file ]
#
#Turn back on spell check script.
Set Variable [ $$stopTest ]
#
Exit Script [ ]
End If
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
testSubsectionGroup::name; ascending
testSubsectionTemplate::order; based on value list: “order Pulldown List”
testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
#
#Conditionally format item and its tags.
Set Variable [ $$ID ]
If [ $editingOneSubsection = 1 ]
Show Custom Dialog [ Message: "Test items can ONLY be added and removed from the subsection being edited. To edit ALL
subsections' test items, 1) click the back buttons until you return to Library Setup. 2) Click Test, and 3) click 2-3-4
templates."; Default Button: “OK”, Commit: “Yes” ]
End If
Perform Script [ “loadSetupTestSubsection” ]
#
#If coming from the test or report module show
#user the Tag Menus window as they probably
#want to edit a tag or add a new tag.
If [ $$module = "testMenuTestItem" or $$module = "reportTagItem" ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “menuTestItem” ]
End If
#
#Turn back on spell check script.
Set Variable [ $$stopTest ]
#
#
