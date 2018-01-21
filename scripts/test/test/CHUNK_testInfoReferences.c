January 15, 2018 14:54:50 Library.fmp12 - CHUNK_testInfoReferences -1-
test: test: CHUNK_testInfoReferences
#
#If the info record has references then make sure
#the Reference window is open, and then load up
#its reference records, otherwise exit the script.
If [ testlearnReportTags::kcreference = "" ]
Exit Script [ ]
End If
#
#Prevent halting to loadTagRecord script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Set Variable [ $$stopWhenLoadingInfoRecordReferences; Value:1 ]
#
#Capture the keys of the references load.
Set Variable [ $references; Value:testlearnReportTags::kcreference ]
#
#Determine how many references there are.
Set Variable [ $numberOfReferences; Value:ValueCount ( testlearnReportTags::kcreference ) ]
#
#Prevent loading up records.
Set Variable [ $$stoploadtestinfo; Value:1 ]
#
#Now go the Reference window or open one up
#if neccessary.
Select Window [ Name: "Reference"; Current file ]
If [ Get ( LastError ) = 112 ]
If [ $$pictureWindowColor = "test" ]
New Window [ Name: "Reference"; Width: Get ( ScreenWidth ) / 3; Left: ( Get ( ScreenWidth ) / 3 ) * 2; Style: Document;
Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Else
New Window [ Name: "Reference"; Width: 290; Left: Get ( ScreenWidth ) - 290; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
End If
End If
#
#Go the layout for info references.
Go to Layout [ “TestInfoReference” (reference) ]
#
#Turn back on record load script.
Set Variable [ $$stoploadtestinfo ]
#
#Find the first reference.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; GetValue ( $references ; $numberOfReferences ) ]
Perform Find [ ]
#
#If there is more than one reference, then load
#find them one-at-time until all have been found.
Loop
Set Variable [ $numberOfReferences; Value:$numberOfReferences - 1 ]
#
Exit Loop If [ $numberOfReferences = 0 ]
#
Enter Find Mode [ ]
Set Field [ reference::_Lreference; GetValue ( $references ; $numberOfReferences ) ]
Extend Found Set [ ]
#
End Loop
#
#Sor the references by keyword (subject).
Perform Script [ “sortRefBySubject (new)” ]
#
#Resize the Reference window along with the
#other windows. The Test and Report sections
#have different window size requirements.
If [ $$pictureWindowColor = "test" ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 3; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 3; Left: Get ( ScreenWidth ) / 3 ]
Select Window [ Name: "Tag Menus"; Current file ]
Else
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get ( ScreenWidth ) - 884 < 334 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: 334; Left: 594 ]
Else
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) - 884; Left: 594 ]
End If
End If
#
#Turn back on info record record's load script.
Set Variable [ $$stopWhenLoadingInfoRecordReferences ]
#
#
