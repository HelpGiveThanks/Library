testScreens: setup: testNameToRevertNamField
If [ $$stopTest = "" ]
Set Variable [ $$tag; Value:test::_Ltest ]
Perform Script [ “CHUNKcheckForDragPasteChanges” ]
Set Variable [ $$tag ]
Set Field [ test::testNameRevert; test::testName ]
End If
January 7, 平成26 12:19:46 Imagination Quality Management.fp7 - testNameToRevertNamField -1-
