January 21, 2018 12:04:28 Library.fmp12 - gotoTechView -1-
test: setup: gotoTechView
If [ $$techView = 1 ]
Select Window [ Name: "Setup"; Current file ]
Go to Layout [ “setupTestSubsection” (testSubsectionTemplate) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Set Variable [ $$techView ]
Else
Select Window [ Name: "Setup"; Current file ]
Go to Layout [ “testSetupTechView” (testSubsectionTemplate) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItemTechView” (tagMenus) ]
Set Variable [ $$techView; Value:1 ]
End If
