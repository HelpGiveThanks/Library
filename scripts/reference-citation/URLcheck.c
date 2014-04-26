reference(citation): URLcheck
If [ $$stopFileNameCheck = 1 ]
Exit Script [ ]
End If
If [ Filter ( reference::ﬁleName ; "?" ) = "?" or
Filter ( reference::ﬁleName ; "#" ) = "#" or
Filter ( reference::ﬁleName ; ";" ) = ";" or
Filter ( reference::ﬁleName ; "/" ) = "/" or
Filter ( reference::ﬁleName ; ":" ) = ":" ]
Show Custom Dialog [ Message: "These special characters ? # / ; : prevent the system from opening ﬁles. Remove them from your ﬁlename and then test the 'ﬁle' button above to insure it opens your ﬁle."; Buttons: “OK” ]
Go to Field [ reference::ﬁleName ]
End If
April 26, 平成26 14:17:47 Imagination Quality Management.fp7 - URLcheck -1-