testScreens: test: step3_OpenOneItemJustLook
#
#
If [ tlResults::InspectionItemCount ≠ "" ]
#note item's ID number and name
Set Variable [ $$item; Value:InspectItems::_Ltest ]
#
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
#
#ﬁnd and show all inspection ﬁndings
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: testlearn::<Field Missing>; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
If [ testlearn::InspectionItemCountLocation = "N/A" or
testlearn::InspectionItemCountLocation = "OK" or
testlearn::InspectionItemCountLocation = "★" ]
Omit Record
Go to Record/Request/Page
[ Previous ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Record/Request/Page
[ Last ]
Loop
Exit Loop If [ testlearn::<Field Missing> = $$Location ]
Go to Record/Request/Page
[ Previous; Exit after last ]
End Loop
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
End If
January 7, 平成26 12:33:21 Imagination Quality Management.fp7 - step3_OpenOneItemJustLook -1-
