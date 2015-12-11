testScreens: testReport: reportPreviewClose
#
#Close print preview window and change menu
#set, so user can no longer change records and
#no longer sees 'Browse Mode' edit menu option.
If [ $$preview = 1 ]
Close Window [ Current Window ]
Install Menu Set [ “HGT” ]
End If
Set Variable [ $$preview ]
December 11, ଘ౮27 1:15:48 Library.fp7 - reportPreviewClose -1-
