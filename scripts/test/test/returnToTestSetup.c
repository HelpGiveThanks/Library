January 15, 2018 15:23:36 Library.fmp12 - returnToTestSetup -1-
test: test: returnToTestSetup
#
#If on test screen, see if any sections have results.
If [ Get (LayoutName) = "testingSubsectionMenu" ]
Set Variable [ $testInUseCheck; Value:1 ]
Go to Record/Request/Page
[ First ]
Loop
If [ testResultsTestSection::countOfONESubsectionsTestResults ≠ "" ]
Set Variable [ $InUse; Value:1 ]
End If
Exit Loop If [ testResultsTestSection::countOfONESubsectionsTestResults ≠ "" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Close any open test item reference windows.
#NOTE: This is next loop is a work around to
#deal with the Reference window issue.
#Basically, there are several scripts that may
#open Reference windows for Info records that
#have references. Rather than try to figure out all
#the ways this occurs (easy with time), this loop
#just closes as many Reference windows as are
#currently open. Not the best solution, but it
#works and I really want to close out work on this
#4.0beta version and move on.
Loop
If [ ValueCount ( FilterValues ( WindowNames ( Get ( FileName ) ) ; "Reference" ) ) > 0 ]
Close Window [ Name: "Reference"; Current file ]
Set Variable [ $resizeTagMenusWindow; Value:1 ]
End If
Exit Loop If [ ValueCount ( FilterValues ( WindowNames ( Get ( FileName ) ) ; "Reference" ) ) = 0 ]
End Loop
#
#Turn off this subsection menu variable.
#Prevents user activating any buttons, until a
#subsection record is loaded.
Set Variable [ $$stopLoadingTestSubSection ]
#
#Turn of the test subject lock variable.
Set Variable [ $$testSubjectIsLocked ]
#
#Go to the Setup Test layout.
Go to Layout [ “defaultTest” (testSectionCreatedFromATemplate) ]
Set Window Title [ Current Window; New Title: "Setup" ]
#
#Make sure window fills half of the screen.
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
#
#Go to Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) /
2; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
End If
#
#Make sure window to fills half of the screen.
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) /
2 ]
#
Go to Layout [ “defaultsAll” (tempSetup) ]
Perform Script [ “defaultsAll (update)” ]
#
#Find all created test section records.
Select Window [ Name: "Setup"; Current file ]
Go to Layout [ “defaultTest” (testSectionCreatedFromATemplate) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Show All Records
#
#Sort
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubjectName::tag; ascending
testSectionCreatedFromATemplate::reportNumber; descending
testSectionCreatedFromATemplate::order; based on value list: “order Pulldown List”
testSectionCreatedFromATemplate::name; ascending ]
[ Restore; No dialog ]
#
#Go to selected test subsection record.
Go to Record/Request/Page [ $$TSRecordNumber ]
[ No dialog ]
Set Variable [ $$tagtest ]
Set Variable [ $$testSubsection ]
Set Variable [ $$TSRecordNumber ]
Set Variable [ $$pictureWIndowColor ]
#
#Conditionally format records.
If [ $InUse = "" and $testInUseCheck = 1 ]
Set Field [ testSectionCreatedFromATemplate::inUse; "" ]
Else If [ $InUse = 1 and $testInUseCheck = 1 and testSectionCreatedFromATemplate::inUse ≠ "d" ]
Set Field [ testSectionCreatedFromATemplate::inUse; "t" ]
End If
#
