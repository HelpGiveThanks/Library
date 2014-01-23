reference(citation): URLcheck
If [ $$stopFileNameCheck = 1 ]
Exit Script [ ]
End If
If [ Filter ( reference::ﬁleName ; "?" ) = "?" or
Filter ( reference::ﬁleName ; "#" ) = "#" or
Filter ( reference::ﬁleName ; ";" ) = ";" or
Filter ( reference::ﬁleName ; ":" ) = ":" ]
Show Custom Dialog [ Message: "These special characters ? # ; : prevent the system from opening ﬁles. Remove them from your ﬁlename and then test the 'ﬁle' button above to insure it opens your ﬁle."; Buttons: “OK” ]
Go to Field [ reference::ﬁleName ]
End If
January 7, 平成26 17:54:06 Imagination Quality Management.fp7 - URLcheck -1-
