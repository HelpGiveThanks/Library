January 15, 2018 14:57:04 Library.fmp12 - testItemCheckTemplateButton -1-
test: test: testItemCheckTemplateButton
#
#
#If a check is showing change the item into text
#or form item.
If [ tagMenus::notesOrCopyright = "✓" ]
Perform Script [ “testItemCheckOrTextOrForm” ]
#
#
#If no check (no button) is showing then
#go to the text field, which is what the user is
#seeing when then click here.
Else
Go to Field [ tagMenus::tag ]
End If
#
#
