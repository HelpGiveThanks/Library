testScreens: setup: gotoTechView
If [ $$techView = 1 ]
Select Window [ Name: "Setup"; Current file ]
Go to Layout [ “testSetup” (test) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Set Variable [ $$techView ]
Else
Select Window [ Name: "Setup"; Current file ]
Go to Layout [ “testSetupTechView” (test) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItemTechView” (tagMenus) ]
Set Variable [ $$techView; Value:1 ]
End If
August 20, ଘ౮28 14:23:54 Library.fp7 - gotoTechView -1-
