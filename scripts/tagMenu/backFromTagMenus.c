tagMenu: backFromTagMenus
If [ Left ( $$openedFrom ; 4 ) = "step" ]
Close Window [ Current Window ]
Else If [ Get (WindowName) = "Tag Menus" ]
Select Window [ Name: "Setup"; Current ﬁle ]
Else If [ Get (WindowName) = "Recommendations" ]
Select Window [ Name: "Report"; Current ﬁle ]
End If
January 7, 平成26 15:35:38 Imagination Quality Management.fp7 - backFromTagMenus -1-
