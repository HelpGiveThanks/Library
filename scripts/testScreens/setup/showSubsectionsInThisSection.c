January 12, 2018 14:04:10 Library.fmp12 - showSubsectionsInThisSection -1-
test: setup: showSubsectionsInThisSection
#
#
Go to Field [ ]
#Set all variables needed for performing various
#scripts while in test setup mode.
If [ $$setupTestSection = "" ]
Set Variable [ $$setupTestSection; Value:testSection::_Ltag ]
Set Variable [ $setupTestSectionName; Value:testSection::tag ]
Go to Field [ ]
#
#
Set Variable [ $$stopTest; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Set Variable [ $$stopTest ]
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::kcsections; $$setupTestSection ]
Perform Find [ ]
Set Variable [ $numberInThisSection; Value:Get (FoundCount) ]
Close Window [ Current Window ]
#
Refresh Window
#
#
#
If [ $numberInThisSection = 0 ]
#
Set Variable [ $$setupTestSection ]
Show Custom Dialog [ Message: "There are no subsections in this test section — " & $setupTestSectionName & "."; Default
Button: “OK”, Commit: “Yes” ]
Refresh Window
#
Else
Select Window [ Name: "Test Templates"; Current file ]
Refresh Window
If [ $numberInThisSection = 1 ]
Show Custom Dialog [ Message: "The " & $numberInThisSection & " subsection in this test section — " &
$setupTestSectionName & " — is now highlighed."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "All " & $numberInThisSection & " subsections in this test section — " &
$setupTestSectionName & " — are now highlighed."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
Else
Set Variable [ $$setupTestSection ]
Select Window [ Name: "Test Templates"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
End If
