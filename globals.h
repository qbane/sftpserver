#ifndef GLOBALS_H
#define GLOBALS_H

#if HAVE_PTHREAD_H
extern struct queue *workqueue;
/* Queue to which jobs are sent */
#endif

extern const struct sftpprotocol sftpv3, sftppreinit;
extern const struct sftpprotocol *protocol;
extern const char sendtype[];

#endif /* GLOBALS_H */

/*
Local Variables:
c-basic-offset:2
comment-column:40
fill-column:79
indent-tabs-mode:nil
End:
*/