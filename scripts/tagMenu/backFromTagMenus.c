January 21, 2018 11:39:19 Library.fmp12 - backFromTagMenus -1-
tagMenu: backFromTagMenus
If [ Left ( $$openedFrom ; 4 ) = "step" ]
Close Window [ Current Window ]
Else If [ Get (WindowName) = "Tag Menus" ]
Select Window [ Name: "Setup"; Current file ]
Else If [ Get (WindowName) = "Recommendations" ]
Select Window [ Name: "Report"; Current file ]
End If
