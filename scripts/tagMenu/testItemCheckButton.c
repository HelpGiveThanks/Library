January 15, 2018 17:00:54 Library.fmp12 - testItemCheckButton -1-
tagMenu: testItemCheckButton
#
#
#On the test-item layout, set this stop check
#or text variable to allows the user to click into
#this field for the purpose of navigating to a
#new record without changing the check or
#text mark status.
If [ $$stopCheckOrTest = 1 ]
Set Variable [ $$stopCheckOrTest ]
Exit Script [ ]
End If
#
#
#Inform the checkORaddTestItem that the
#check button was clicked as it may be hidden
#if the user clicked on a text T item, in which
#case the user expects to go to the text field.
Set Variable [ $$checkButton; Value:1 ]
#
Perform Script [ “checkORaddTestItem (update name change testAddTestItemTextOrKey)” ]
#
#
