#ifndef __TRACEPOINT_H__
#define __TRACEPOINT_H__

typedef unsigned int CORE_ADDR;
typedef unsigned long ULONGEST;

enum tracepoint_type
{
	/* Trap based tracepoint.  */
	trap_tracepoint,

	/* A fast tracepoint implemented with a jump instead of a trap.  */
	fast_tracepoint,

	/* A static tracepoint, implemented by a program call into a tracing
	   library.  */
	static_tracepoint
};


struct tracepoint
{
  /* The number of the tracepoint, as specified by GDB.  Several
     tracepoint objects here may share a number.  */
  int number;

  /* Address at which the tracepoint is supposed to trigger.  Several
     tracepoints may share an address.  */
  CORE_ADDR address;

  /* Tracepoint type.  */
  enum tracepoint_type type;

  /* True if the tracepoint is currently enabled.  */
  int enabled;

  /* The number of single steps that will be performed after each
     tracepoint hit.  */
  long step_count;

  /* The number of times the tracepoint may be hit before it will
     terminate the entire tracing run.  */
  long pass_count;

  /* Pointer to the agent expression that is the tracepoint's
     conditional, or NULL if the tracepoint is unconditional.  */
  struct agent_expr *cond;

  /* The list of actions to take when the tracepoint triggers.  */
  int numactions;
  struct tracepoint_action **actions;

  /* Count of the times we've hit this tracepoint during the run.
     Note that while-stepping steps are not counted as "hits".  */
  long hit_count;

  CORE_ADDR compiled_cond;

  /* Link to the next tracepoint in the list.  */
  struct tracepoint *next;

  /* The list of actions to take when the tracepoint triggers, in
     string/packet form.  */
  char **actions_str;

  /* The collection of strings that describe the tracepoint as it was
     entered into GDB.  These are not used by the target, but are
     reported back to GDB upon reconnection.  */
  struct source_string *source_strings;

  /* The number of bytes displaced by fast tracepoints. It may subsume
     multiple instructions, for multi-byte fast tracepoints.  This
     field is only valid for fast tracepoints.  */
  int orig_size;

  /* Only for fast tracepoints.  */
  CORE_ADDR obj_addr_on_target;

  /* Address range where the original instruction under a fast
     tracepoint was relocated to.  (_end is actually one byte past
     the end).  */
  CORE_ADDR adjusted_insn_addr;
  CORE_ADDR adjusted_insn_addr_end;

  /* The address range of the piece of the jump pad buffer that was
     assigned to this fast tracepoint.  (_end is actually one byte
     past the end).*/
  CORE_ADDR jump_pad;
  CORE_ADDR jump_pad_end;

  /* The list of actions to take while in a stepping loop.  These
     fields are only valid for patch-based tracepoints.  */
  int num_step_actions;
  struct tracepoint_action **step_actions;
  /* Same, but in string/packet form.  */
  char **step_actions_str;

  /* Handle returned by the breakpoint or tracepoint module when we
     inserted the trap or jump, or hooked into a static tracepoint.
     NULL if we haven't inserted it yet.  */
  void *handle;
};



int handle_tracepoint_packets(const char *cmd);
static int cmd_qtdp(const char *cmd);
char * unpack_varlen_hex (char *buff,  ULONGEST *result);
void convert_ascii_to_int (const char *from, unsigned char *to, int n);

#endif /* __TRACEPOINT_H__  */
