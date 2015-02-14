startclose: start
Show/Hide Status Area
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
#
#capture filepath for use in importing this files data
Go to Layout [ “tempStart” (TEMP) ]
New Record/Request
Paste [ TEMP::import ]
[ Select ]
Set Field [ TEMP::filePath; Get (FilePath) ]
If [ TEMP::import = "adﬂki3ina;lkfjie8;la;lkdvnma;ldieiasoerueoilanldf83984798374iwuhelfkjdlsidufioawkel" ]
Set Window Title [ Current Window; New Title: "import" ]
End If
Set Field [ TEMP::import; "" ]
Copy [ TEMP::filePath ]
[ Select ]
Delete Record/Request
[ No dialog ]
Close Window [ Name: "import"; Current file ]
Go to Layout [ original layout ]
January 7, 平成26 12:01:02 Imagination Quality Management.fp7 - start -1-
