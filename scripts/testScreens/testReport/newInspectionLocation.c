testScreens: testReport: NewInspectionLocation
#
If [ TEMP::ksection = "" ]
Go to Field [ TEMP::ksection ]
[ Select/perform ]
Halt Script
Else If [ TEMP::reportNumber = "" ]
Go to Field [ TEMP::reportNumber ]
[ Select/perform ]
Halt Script
Else If [ TEMP::LocationName = "" ]
Show Custom Dialog [ Message: "A new test focus must have a name picked from the default test focus list, which will be displayed after you click OK."; Buttons: “OK” ]
Go to Field [ TEMP::kfocus ]
[ Select/perform ]
Go to Object [ Object Name: "focus" ]
Halt Script
Else If [ TEMP::kdefaultNodeTestSubject = "" ]
Show Custom Dialog [ Message: "New test focuses are created for specific test nodes. Pick one or create a new one in the node section before creating a new test focus."; Buttons: “OK” ]
Halt Script
End If
Set Variable [ $tag; Value:TEMP::kfocus ]
Set Variable [ $$stopFocusLoad; Value:1 ]
#Had to capture report number as variable or
#stop record load script which would replace
#the Temp with nothing upon new record creation.
#I decided to capture it.
Set Variable [ $reportNumber; Value:TEMP::reportNumber ]
Set Variable [ $mod1; Value:TEMP::kmodifier1 ]
Set Variable [ $mod2; Value:TEMP::kmodifier2 ]
New Record/Request
Set Variable [ $nodeLocation; Value:tagTestSubjectLocation::_LtestSubjectLocation ]
Set Field [ tagTestSubjectLocation::knode; TEMP::kdefaultNodeTestSubject ]
Set Field [ tagTestSubjectLocation::ksection; TEMP::ksection ]
Set Field [ tagTestSubjectLocation::reportNumber; $reportNumber ]
Set Field [ tagTestSubjectLocation::kfocus; TEMP::kfocus ]
Set Field [ tagTestSubjectLocation::kfocusAttribute1; TEMP::kmodifier1 ]
Set Field [ tagTestSubjectLocation::kfocusAttribute2; TEMP::kmodifier2 ]
Set Field [ tagTestSubjectLocation::focusName; TextStyleAdd (
TEMP::LocationName
; Lowercase ) ]
Set Field [ tagTestSubjectLocation::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Layout [ original layout ]
Sort Records [ ]
[ No dialog ]
Set Field [ TEMP::reportNumber; tagTestSubjectLocation::reportNumber ]
Set Variable [ $$stopFocusLoad ]
Go to Field [ tagTestSubjectLocation::focusName ]
January 7, 平成26 14:16:02 Imagination Quality Management.fp7 - NewInspectionLocation -1-
