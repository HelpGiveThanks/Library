testScreens: testReport: newInspectionLocation
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
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
Show Custom Dialog [ Message: "Click on the test-section pulldown list (now highlighted for you) and pick a test section to add to your test."; Buttons: “OK” ]
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
December 9, ଘ౮27 20:50:10 Library.fp7 - newInspectionLocation -1-
