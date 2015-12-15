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
December 15, ଘ౮27 12:07:27 Library.fp7 - gotoTechView -1-
