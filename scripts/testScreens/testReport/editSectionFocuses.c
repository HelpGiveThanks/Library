testScreens: testReport: editSectionFocuses
#
#If there are no tests, then stop this script as there
#are no test to create things for.
If [ TEMP::ktest = "" ]
Show Custom Dialog [ Message: "There are no tests."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Go to Layout [ “setupTestFocus” (tagLocation) ]
#
#Find all test focuses for this test.
#New tests will not have any foci so
#error capture needs to be turned on.
Set Error Capture [ On ]
Allow User Abort [ Off ]
View As
[ View as List ]
Enter Find Mode [ ]
Set Field [ tagLocation::ksection; TEMP::ksection ]
Set Field [ tagLocation::match; "focus" ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: tagLocation::tag; ascending ]
[ Restore; No dialog ]
Perform Script [ “insureEqualityOfSpellFields” ]
January 7, 平成26 14:31:21 Imagination Quality Management.fp7 - editSectionFocuses -1-
