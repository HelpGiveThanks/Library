tagMenu: gotoLessDetailLayout
#
#If in add mode, keep user on the evenMore layout.
If [ $$add = 1 ]
Show Custom Dialog [ Message: "Turn off add mode (click 'add' button) to reduce number of pictures shown and full link names."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Reveal more or fewer pictures and links for tag.
If [ Right ( Get (LayoutName) ; 8 ) = "evenmore" ]
Go to Layout [ “testMenuTestItemMORE” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "more" ]
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
#
#Remember layout user is on so they can be
#returned to correct view.
Set Field [ TEMP::DetailmoreORLessLayout; Get (LayoutName) ]
January 7, 平成26 16:37:05 Imagination Quality Management.fp7 - gotoLessDetailLayout -1-
