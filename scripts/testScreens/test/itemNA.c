testScreens: test: ItemNA
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
If [ tlResults::_Ltestlearn = "" ]
Freeze Window
New Window [ ]
#note item's ID number and name
Set Variable [ $$item; Value:InspectItems::_Ltest ]
Set Variable [ $$itemName; Value:InspectItems::testName ]
Set Field [ TEMP::testName ]
Go to Layout [ “discoveries” (testlearn) ]
New Record/Request
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::Location; $$locationName ]
Set Field [ testlearn::kcsection; $$Library ]
Set Field [ testlearn::ktest; $$item ]
#lock item location so it cannot be deleted unless all ﬁndings for it are deleted
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "t" ]
#reﬁnd all location records for this session
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ tlResults::InspectionItemCountLocation; "N/A" ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Go to Field [ ]
Close Window [ Current Window ]
Exit Script [ ]
Else If [ tlResults::InspectionItemCountLocation = "" and
tlResults::_Ltestlearn ≠ "" ]
Set Field [ tlResults::InspectionItemCountLocation; "N/A" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Set Field [ TEMP::testName ]
Go to Field [ ]
Exit Script [ ]
Else If [ tlResults::InspectionItemCountLocation = "N/A" ]
Set Field [ tlResults::InspectionItemCountLocation; "OK" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Set Field [ TEMP::testName ]
Go to Field [ ]
Exit Script [ ]
Else If [ tlResults::InspectionItemCountLocation = "N/A" or
tlResults::InspectionItemCountLocation = "OK" ]
If [ TLResultsOnReport::InspectionItemCount = "" ]
Set Field [ TEMP::testName ]
Show Custom Dialog [ Title: "FYI"; Message: "Use the star symbol to referr to other assessment ﬁndings. You currently do not have any for this item."; Buttons: “OK” ]
Set Field [ tlResults::InspectionItemCountLocation; "" ]
Go to Field [ ]
Freeze Window
New Window [ ]
#note item's ID number and name
Set Variable [ $$item; Value:InspectItems::_Ltest ]
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::ktest; $$item ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
#Unlock Item Location
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
#reﬁnd all location records for this session
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
End If
Close Window [ Current Window ]
Exit Script [ ]
End If
Set Field [ tlResults::InspectionItemCountLocation; "★" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Go to Field [ ]
Exit Script [ ]
Else If [ tlResults::InspectionItemCountLocation ≠ "N/A" and
tlResults::InspectionItemCountLocation ≠ "OK" and
tlResults::InspectionItemCountLocation ≠ "★" ]
Set Field [ TEMP::testName ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Go to Field [ ]
Exit Script [ ]
End If
Freeze Window
New Window [ ]
#note item's ID number and name
Set Variable [ $$item; Value:InspectItems::_Ltest ]
Set Field [ TEMP::testName ]
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::ktest; $$item ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
#Unlock Item Location
Enter Find Mode [ ]
January 7, 平成26 12:42:43 Imagination Quality Management.fp7 - ItemNA -1-testScreens: test: ItemNA
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
#reﬁnd all location records for this session
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
End If
Close Window [ Current Window ]
January 7, 平成26 12:42:43 Imagination Quality Management.fp7 - ItemNA -2-
