January 15, 2018 14:53:45 Library.fmp12 - loadTestInfo -1-
test: test: loadTestInfo
#
#This first section is key to stopping this script
#when another script for example loops thru
#many records each of which would trigger this
#script and really slow down the program and
#create strobe effect that is really irritating to
#look at.
If [ $$stoploadtestinfo = 1 or $$stopPart3InProgress = 1 ]
Exit Script [ ]
End If
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Reset conditional formatting variables.
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $$infoPictureUsedOnThisTestSubSection ]
Set Variable [ $$main; Value:testlearnReportTags::_Ltestlearn ]
Go to Field [ ]
#
#Get this record's test tag keys, used by sort
#order number script.
Set Variable [ $$test; Value:testlearnReportTags::kctestSubsectionInfo ]
#
#Look thru the report picture fields to see if
#any of them are using this info record's
#picture or text.
If [ testlearnReportTags::inUseNumberOfTimes > 0 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableReport” (report) ]
#
#See if any picture 1 slots use this info.
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::kTag1; $$main ]
Perform Find [ ]
#
If [ Get (FoundCount) > 0 ]
Set Variable [ $$infoPictureUsedOnThisTestSubSection; Value:1 ]
Set Variable [ $$stoploadtestinfo ]
Close Window [ Current Window ]
End If
#
#See if any picture 2 slots use this info.
If [ $$infoPictureUsedOnThisTestSubSection = "" ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::kTag2; $$main ]
Perform Find [ ]
#
If [ Get (FoundCount) > 0 ]
Set Variable [ $$infoPictureUsedOnThisTestSubSection; Value:1 ]
Set Variable [ $$stoploadtestinfo ]
Close Window [ Current Window ]
End If
End If
#
#See if any picture 3 slots use this info.
If [ $$infoPictureUsedOnThisTestSubSection = "" ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::kTag3; $$main ]
Perform Find [ ]
#
If [ Get (FoundCount) > 0 ]
Set Variable [ $$infoPictureUsedOnThisTestSubSection; Value:1 ]
Set Variable [ $$stoploadtestinfo ]
Close Window [ Current Window ]
End If
End If
#
#See if any picture 4 slots use this info.
If [ $$infoPictureUsedOnThisTestSubSection = "" ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::kTag4; $$main ]
Perform Find [ ]
#
If [ Get (FoundCount) > 0 ]
Set Variable [ $$infoPictureUsedOnThisTestSubSection; Value:1 ]
End If
#
#Close this search window whether pictures
#are found in the number 4 slot or no pictures
#are found.
Set Variable [ $$stoploadtestinfo ]
Close Window [ Current Window ]
End If
End If
#
#Refresh conditional formatting in both
#windows and return to Tag Menus window.
Select Window [ Name: "Report"; Current file ]
If [ Get ( LastError ) = 0 ]
Set Variable [ $$userReportColorsInTextWindow; Value:1 ]
Else
Set Variable [ $$userReportColorsInTextWindow ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Allow user to click into selected record's
#text window.
Set Variable [ $$stopOpenNewTextWindow ]
#
#Prevent the opening of the record's text
#window when user goes to the record.
Set Variable [ $$stopOpenNewTextWindow; Value:1 ]
#
#Only open a Reference window if the selected
#info record has references, and if the user is
#not in the process of going to the Learn
#module to edit info records attached to
#this subsection.
If [ $$doNotOpenReferenceWindow ≠ 1 and ValueCount ( testlearnReportTags::kcreference ) - Length ( Filter ( testlearnReportTags::
kcreference ; "L" ) ) > 0 ]
Perform Script [ “CHUNK_testInfoReferences” ]
#
#
#If there are no reference records for this info
#record, then make sure to close the Reference
#window (if opened for the last info record
#selected) and resize the two remaining windows.
Else
Close Window [ Name: "Reference"; Current file ]
If [ $$pictureWindowColor = "test" ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2 ]
#
#The size of the Tag Menus window in the Report
#section can be larger than half the window width.
Else
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get (ScreenWidth) - 594; Left: 594 ]
End If
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#
