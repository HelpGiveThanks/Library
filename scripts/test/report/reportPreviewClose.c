January 21, 2018 11:04:47 Library.fmp12 - reportPreviewClose -1-
test: report: reportPreviewClose
#
#Close print preview window and change menu
#set, so user can no longer change records and
#no longer sees 'Browse Mode' edit menu option.
If [ $$preview = 1 ]
Close Window [ Current Window ]
Install Menu Set [ “HGT” ]
End If
Set Variable [ $$preview ]
