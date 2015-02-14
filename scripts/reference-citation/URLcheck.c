reference(citation): URLcheck
If [ $$stopFileNameCheck = 1 ]
Exit Script [ ]
End If
If [ Filter ( reference::fileName ; "?" ) = "?" or
Filter ( reference::fileName ; "#" ) = "#" or
Filter ( reference::fileName ; ";" ) = ";" or
Filter ( reference::fileName ; "/" ) = "/" or
Filter ( reference::fileName ; ":" ) = ":" ]
Show Custom Dialog [ Message: "These special characters ? # / ; : prevent the system from opening files. Remove them from your filename and then test the 'file' button above to insure it opens your file."; Buttons: “OK” ]
Go to Field [ reference::fileName ]
End If
April 26, 平成26 14:17:47 Imagination Quality Management.fp7 - URLcheck -1-
