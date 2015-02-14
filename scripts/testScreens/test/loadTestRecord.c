testScreens: test: loadTestRecord
#Prevents script from running to speed up other
#scripts that keep calling it up by looping thru
#multiple records.
If [ $$stopLoadTestRecord = 1 ]
Exit Script [ ]
End If
Set Variable [ $$evidenceToBeTagged; Value:testlearn::_Ltestlearn ]
Set Variable [ $$taggedEvidence; Value:testlearn::kcKeywordOther ]
Set Variable [ $$testItem ]
Set Variable [ $$testItem; Value:testlearn::kctestItem ]
Set Field [ TEMP::EvidenceItemNameAndNumber; testlearn::_Number & " " & InspectItems::testName ]
Set Variable [ $windowName; Value:Get (WindowName) ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Select Window [ Name: $windowName; Current file ]
Refresh Window
// Perform Script [ “evidenceDetailDELETE?????” ]
January 7, 平成26 12:25:06 Imagination Quality Management.fp7 - loadTestRecord -1-
