January 15, 2018 14:58:13 Library.fmp12 - testItemTextOrFormTemplateButton -1-
test: test: testItemTextOrFormTemplateButton
#
#
#If a T is showing change the item into an FT
#item, and if an FT is showing change the item
#into a check item.
If [ tagMenus::notesOrCopyright = "FT" or tagMenus::notesOrCopyright = "T" ]
Perform Script [ “testItemCheckOrTextOrForm (new)” ]
#
#
#If neither a T or FT (no button) is showing then
#go to the text field, which is what the user is
#seeing when then click here.
Else
Go to Field [ tagMenus::tag ]
End If
#
#
