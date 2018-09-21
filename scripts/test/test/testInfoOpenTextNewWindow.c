September 20, 2018 17:52:40 Library.fmp12 - testInfoOpenTextNewWindow -1-
test: test: testInfoOpenTextNewWindow
#
#Prevent the opening of the record's text
#window when user goes to the record.
If [ $$stopOpenNewTextWindow = 1 ]
Set Variable [ $$stopOpenNewTextWindow ]
Exit Script [ ]
End If
#
#Stop record load script while new window
#is opened.
Go to Field [ ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
New Window [ Name: "Tag Menus"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
#
#If record is locked go to locked layout.
If [ $$lockedMainLearnRecord = "" ]
Scroll Window
[ Home ]
Go to Layout [ “testInfoText” (testlearnReportTags) ]
#
Else If [ $$lockedMainLearnRecord ≠ "" ]
Go to Layout [ “testInfoTextLocked” (testlearnReportTags) ]
End If
#
#If the user in on an iDevice...
If [ Get ( SystemPlatform ) = 3 and $$showPinchAndZoommessageOnlyOnce = "" ]
Show Custom Dialog [ Message: "Use the two-finger pinch-and-zoom gesture to enlarge everything for easier viewing. (This
message is shown once per session.)"; Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$showPinchAndZoommessageOnlyOnce; Value:1 ]
End If
#
#Turn back on record load script and pause
#while user looks at text.
Set Variable [ $$stopLoadTestInfo ]
Pause/Resume Script [ Indefinitely ]
#
