January 12, 2018 14:05:53 Library.fmp12 - loadSetupTestSection -1-
test: setup: loadSetupTestSection
#
If [ $$stopTest = 1 ]
Exit Script [ ]
End If
#
#Set all variables needed for performing various
#scripts while in test setup mode.
Set Variable [ $$setupTestSection ]
Refresh Window
Select Window [ Name: "Test Templates"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
