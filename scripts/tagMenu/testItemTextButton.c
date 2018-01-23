January 15, 2018 17:02:08 Library.fmp12 - testItemTextButton -1-
tagMenu: testItemTextButton
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
#text button was clicked as it may be hidden
#if the user clicked on a check item, in which
#case the user expects to go to the text field.
Set Variable [ $$textButton; Value:1 ]
#
Perform Script [ “checkORaddTestItem” ]
#
#
