//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     ANTLR Version: 4.13.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from /mnt/nfs/homes/lannur-s/42/42MiniShell/docs/JollyShellParser.g by ANTLR 4.13.1

// Unreachable code detected
#pragma warning disable 0162
// The variable '...' is assigned but its value is never used
#pragma warning disable 0219
// Missing XML comment for publicly visible type or member '...'
#pragma warning disable 1591
// Ambiguous reference in cref attribute
#pragma warning disable 419

using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;
using Antlr4.Runtime;
using Antlr4.Runtime.Atn;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using DFA = Antlr4.Runtime.Dfa.DFA;

[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.13.1")]
[System.CLSCompliant(false)]
public partial class JollyShellParser : Parser {
	protected static DFA[] decisionToDFA;
	protected static PredictionContextCache sharedContextCache = new PredictionContextCache();
	public const int
		WORD=1, NAME=2, ASSIGNMENT_WORD=3, IO_NUMBER=4, PIPE=5, REDIRECT_IN=6, 
		REDIRECT_OUT=7, HEREDOC=8, APPEND_OUT=9, LINEBREAK=10;
	public const int
		RULE_prompt = 0, RULE_pipeline = 1, RULE_simple_command = 2, RULE_cmd_name = 3, 
		RULE_cmd_word = 4, RULE_cmd_prefix = 5, RULE_cmd_suffix = 6, RULE_io_redirect = 7, 
		RULE_io_redirect_file = 8, RULE_io_here_doc = 9, RULE_here_end = 10, RULE_file_name = 11;
	public static readonly string[] ruleNames = {
		"prompt", "pipeline", "simple_command", "cmd_name", "cmd_word", "cmd_prefix", 
		"cmd_suffix", "io_redirect", "io_redirect_file", "io_here_doc", "here_end", 
		"file_name"
	};

	private static readonly string[] _LiteralNames = {
		null, null, null, null, null, "'|'", "'<'", "'>'", "'<<'", "'>>'", "'\\n'"
	};
	private static readonly string[] _SymbolicNames = {
		null, "WORD", "NAME", "ASSIGNMENT_WORD", "IO_NUMBER", "PIPE", "REDIRECT_IN", 
		"REDIRECT_OUT", "HEREDOC", "APPEND_OUT", "LINEBREAK"
	};
	public static readonly IVocabulary DefaultVocabulary = new Vocabulary(_LiteralNames, _SymbolicNames);

	[NotNull]
	public override IVocabulary Vocabulary
	{
		get
		{
			return DefaultVocabulary;
		}
	}

	public override string GrammarFileName { get { return "JollyShellParser.g"; } }

	public override string[] RuleNames { get { return ruleNames; } }

	public override int[] SerializedAtn { get { return _serializedATN; } }

	static JollyShellParser() {
		decisionToDFA = new DFA[_ATN.NumberOfDecisions];
		for (int i = 0; i < _ATN.NumberOfDecisions; i++) {
			decisionToDFA[i] = new DFA(_ATN.GetDecisionState(i), i);
		}
	}

		public JollyShellParser(ITokenStream input) : this(input, Console.Out, Console.Error) { }

		public JollyShellParser(ITokenStream input, TextWriter output, TextWriter errorOutput)
		: base(input, output, errorOutput)
	{
		Interpreter = new ParserATNSimulator(this, _ATN, decisionToDFA, sharedContextCache);
	}

	public partial class PromptContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public PipelineContext pipeline() {
			return GetRuleContext<PipelineContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode LINEBREAK() { return GetToken(JollyShellParser.LINEBREAK, 0); }
		public PromptContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_prompt; } }
	}

	[RuleVersion(0)]
	public PromptContext prompt() {
		PromptContext _localctx = new PromptContext(Context, State);
		EnterRule(_localctx, 0, RULE_prompt);
		try {
			State = 26;
			ErrorHandler.Sync(this);
			switch (TokenStream.LA(1)) {
			case WORD:
			case ASSIGNMENT_WORD:
			case IO_NUMBER:
			case REDIRECT_IN:
			case REDIRECT_OUT:
			case HEREDOC:
			case APPEND_OUT:
				EnterOuterAlt(_localctx, 1);
				{
				State = 24;
				pipeline(0);
				}
				break;
			case LINEBREAK:
				EnterOuterAlt(_localctx, 2);
				{
				State = 25;
				Match(LINEBREAK);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class PipelineContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public Simple_commandContext simple_command() {
			return GetRuleContext<Simple_commandContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public PipelineContext pipeline() {
			return GetRuleContext<PipelineContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode PIPE() { return GetToken(JollyShellParser.PIPE, 0); }
		public PipelineContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_pipeline; } }
	}

	[RuleVersion(0)]
	public PipelineContext pipeline() {
		return pipeline(0);
	}

	private PipelineContext pipeline(int _p) {
		ParserRuleContext _parentctx = Context;
		int _parentState = State;
		PipelineContext _localctx = new PipelineContext(Context, _parentState);
		PipelineContext _prevctx = _localctx;
		int _startState = 2;
		EnterRecursionRule(_localctx, 2, RULE_pipeline, _p);
		try {
			int _alt;
			EnterOuterAlt(_localctx, 1);
			{
			{
			State = 29;
			simple_command();
			}
			Context.Stop = TokenStream.LT(-1);
			State = 36;
			ErrorHandler.Sync(this);
			_alt = Interpreter.AdaptivePredict(TokenStream,1,Context);
			while ( _alt!=2 && _alt!=global::Antlr4.Runtime.Atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( ParseListeners!=null )
						TriggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new PipelineContext(_parentctx, _parentState);
					PushNewRecursionContext(_localctx, _startState, RULE_pipeline);
					State = 31;
					if (!(Precpred(Context, 1))) throw new FailedPredicateException(this, "Precpred(Context, 1)");
					State = 32;
					Match(PIPE);
					State = 33;
					simple_command();
					}
					} 
				}
				State = 38;
				ErrorHandler.Sync(this);
				_alt = Interpreter.AdaptivePredict(TokenStream,1,Context);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			UnrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public partial class Simple_commandContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public Cmd_prefixContext cmd_prefix() {
			return GetRuleContext<Cmd_prefixContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public Cmd_wordContext cmd_word() {
			return GetRuleContext<Cmd_wordContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public Cmd_suffixContext cmd_suffix() {
			return GetRuleContext<Cmd_suffixContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public Cmd_nameContext cmd_name() {
			return GetRuleContext<Cmd_nameContext>(0);
		}
		public Simple_commandContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_simple_command; } }
	}

	[RuleVersion(0)]
	public Simple_commandContext simple_command() {
		Simple_commandContext _localctx = new Simple_commandContext(Context, State);
		EnterRule(_localctx, 4, RULE_simple_command);
		try {
			State = 51;
			ErrorHandler.Sync(this);
			switch ( Interpreter.AdaptivePredict(TokenStream,2,Context) ) {
			case 1:
				EnterOuterAlt(_localctx, 1);
				{
				State = 39;
				cmd_prefix(0);
				State = 40;
				cmd_word();
				State = 41;
				cmd_suffix(0);
				}
				break;
			case 2:
				EnterOuterAlt(_localctx, 2);
				{
				State = 43;
				cmd_prefix(0);
				State = 44;
				cmd_word();
				}
				break;
			case 3:
				EnterOuterAlt(_localctx, 3);
				{
				State = 46;
				cmd_prefix(0);
				}
				break;
			case 4:
				EnterOuterAlt(_localctx, 4);
				{
				State = 47;
				cmd_name();
				State = 48;
				cmd_suffix(0);
				}
				break;
			case 5:
				EnterOuterAlt(_localctx, 5);
				{
				State = 50;
				cmd_name();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class Cmd_nameContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode WORD() { return GetToken(JollyShellParser.WORD, 0); }
		public Cmd_nameContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_cmd_name; } }
	}

	[RuleVersion(0)]
	public Cmd_nameContext cmd_name() {
		Cmd_nameContext _localctx = new Cmd_nameContext(Context, State);
		EnterRule(_localctx, 6, RULE_cmd_name);
		try {
			EnterOuterAlt(_localctx, 1);
			{
			State = 53;
			Match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class Cmd_wordContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode WORD() { return GetToken(JollyShellParser.WORD, 0); }
		public Cmd_wordContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_cmd_word; } }
	}

	[RuleVersion(0)]
	public Cmd_wordContext cmd_word() {
		Cmd_wordContext _localctx = new Cmd_wordContext(Context, State);
		EnterRule(_localctx, 8, RULE_cmd_word);
		try {
			EnterOuterAlt(_localctx, 1);
			{
			State = 55;
			Match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class Cmd_prefixContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public Io_redirectContext io_redirect() {
			return GetRuleContext<Io_redirectContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode ASSIGNMENT_WORD() { return GetToken(JollyShellParser.ASSIGNMENT_WORD, 0); }
		[System.Diagnostics.DebuggerNonUserCode] public Cmd_prefixContext cmd_prefix() {
			return GetRuleContext<Cmd_prefixContext>(0);
		}
		public Cmd_prefixContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_cmd_prefix; } }
	}

	[RuleVersion(0)]
	public Cmd_prefixContext cmd_prefix() {
		return cmd_prefix(0);
	}

	private Cmd_prefixContext cmd_prefix(int _p) {
		ParserRuleContext _parentctx = Context;
		int _parentState = State;
		Cmd_prefixContext _localctx = new Cmd_prefixContext(Context, _parentState);
		Cmd_prefixContext _prevctx = _localctx;
		int _startState = 10;
		EnterRecursionRule(_localctx, 10, RULE_cmd_prefix, _p);
		try {
			int _alt;
			EnterOuterAlt(_localctx, 1);
			{
			State = 60;
			ErrorHandler.Sync(this);
			switch (TokenStream.LA(1)) {
			case IO_NUMBER:
			case REDIRECT_IN:
			case REDIRECT_OUT:
			case HEREDOC:
			case APPEND_OUT:
				{
				State = 58;
				io_redirect();
				}
				break;
			case ASSIGNMENT_WORD:
				{
				State = 59;
				Match(ASSIGNMENT_WORD);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			Context.Stop = TokenStream.LT(-1);
			State = 68;
			ErrorHandler.Sync(this);
			_alt = Interpreter.AdaptivePredict(TokenStream,5,Context);
			while ( _alt!=2 && _alt!=global::Antlr4.Runtime.Atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( ParseListeners!=null )
						TriggerExitRuleEvent();
					_prevctx = _localctx;
					{
					State = 66;
					ErrorHandler.Sync(this);
					switch ( Interpreter.AdaptivePredict(TokenStream,4,Context) ) {
					case 1:
						{
						_localctx = new Cmd_prefixContext(_parentctx, _parentState);
						PushNewRecursionContext(_localctx, _startState, RULE_cmd_prefix);
						State = 62;
						if (!(Precpred(Context, 3))) throw new FailedPredicateException(this, "Precpred(Context, 3)");
						State = 63;
						io_redirect();
						}
						break;
					case 2:
						{
						_localctx = new Cmd_prefixContext(_parentctx, _parentState);
						PushNewRecursionContext(_localctx, _startState, RULE_cmd_prefix);
						State = 64;
						if (!(Precpred(Context, 1))) throw new FailedPredicateException(this, "Precpred(Context, 1)");
						State = 65;
						Match(ASSIGNMENT_WORD);
						}
						break;
					}
					} 
				}
				State = 70;
				ErrorHandler.Sync(this);
				_alt = Interpreter.AdaptivePredict(TokenStream,5,Context);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			UnrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public partial class Cmd_suffixContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public Io_redirectContext io_redirect() {
			return GetRuleContext<Io_redirectContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode WORD() { return GetToken(JollyShellParser.WORD, 0); }
		[System.Diagnostics.DebuggerNonUserCode] public Cmd_suffixContext cmd_suffix() {
			return GetRuleContext<Cmd_suffixContext>(0);
		}
		public Cmd_suffixContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_cmd_suffix; } }
	}

	[RuleVersion(0)]
	public Cmd_suffixContext cmd_suffix() {
		return cmd_suffix(0);
	}

	private Cmd_suffixContext cmd_suffix(int _p) {
		ParserRuleContext _parentctx = Context;
		int _parentState = State;
		Cmd_suffixContext _localctx = new Cmd_suffixContext(Context, _parentState);
		Cmd_suffixContext _prevctx = _localctx;
		int _startState = 12;
		EnterRecursionRule(_localctx, 12, RULE_cmd_suffix, _p);
		try {
			int _alt;
			EnterOuterAlt(_localctx, 1);
			{
			State = 74;
			ErrorHandler.Sync(this);
			switch (TokenStream.LA(1)) {
			case IO_NUMBER:
			case REDIRECT_IN:
			case REDIRECT_OUT:
			case HEREDOC:
			case APPEND_OUT:
				{
				State = 72;
				io_redirect();
				}
				break;
			case WORD:
				{
				State = 73;
				Match(WORD);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			Context.Stop = TokenStream.LT(-1);
			State = 82;
			ErrorHandler.Sync(this);
			_alt = Interpreter.AdaptivePredict(TokenStream,8,Context);
			while ( _alt!=2 && _alt!=global::Antlr4.Runtime.Atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( ParseListeners!=null )
						TriggerExitRuleEvent();
					_prevctx = _localctx;
					{
					State = 80;
					ErrorHandler.Sync(this);
					switch ( Interpreter.AdaptivePredict(TokenStream,7,Context) ) {
					case 1:
						{
						_localctx = new Cmd_suffixContext(_parentctx, _parentState);
						PushNewRecursionContext(_localctx, _startState, RULE_cmd_suffix);
						State = 76;
						if (!(Precpred(Context, 3))) throw new FailedPredicateException(this, "Precpred(Context, 3)");
						State = 77;
						io_redirect();
						}
						break;
					case 2:
						{
						_localctx = new Cmd_suffixContext(_parentctx, _parentState);
						PushNewRecursionContext(_localctx, _startState, RULE_cmd_suffix);
						State = 78;
						if (!(Precpred(Context, 1))) throw new FailedPredicateException(this, "Precpred(Context, 1)");
						State = 79;
						Match(WORD);
						}
						break;
					}
					} 
				}
				State = 84;
				ErrorHandler.Sync(this);
				_alt = Interpreter.AdaptivePredict(TokenStream,8,Context);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			UnrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public partial class Io_redirectContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public Io_redirect_fileContext io_redirect_file() {
			return GetRuleContext<Io_redirect_fileContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode IO_NUMBER() { return GetToken(JollyShellParser.IO_NUMBER, 0); }
		[System.Diagnostics.DebuggerNonUserCode] public Io_here_docContext io_here_doc() {
			return GetRuleContext<Io_here_docContext>(0);
		}
		public Io_redirectContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_io_redirect; } }
	}

	[RuleVersion(0)]
	public Io_redirectContext io_redirect() {
		Io_redirectContext _localctx = new Io_redirectContext(Context, State);
		EnterRule(_localctx, 14, RULE_io_redirect);
		try {
			State = 91;
			ErrorHandler.Sync(this);
			switch ( Interpreter.AdaptivePredict(TokenStream,9,Context) ) {
			case 1:
				EnterOuterAlt(_localctx, 1);
				{
				State = 85;
				io_redirect_file();
				}
				break;
			case 2:
				EnterOuterAlt(_localctx, 2);
				{
				State = 86;
				Match(IO_NUMBER);
				State = 87;
				io_redirect_file();
				}
				break;
			case 3:
				EnterOuterAlt(_localctx, 3);
				{
				State = 88;
				Match(IO_NUMBER);
				State = 89;
				io_here_doc();
				}
				break;
			case 4:
				EnterOuterAlt(_localctx, 4);
				{
				State = 90;
				io_here_doc();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class Io_redirect_fileContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode REDIRECT_IN() { return GetToken(JollyShellParser.REDIRECT_IN, 0); }
		[System.Diagnostics.DebuggerNonUserCode] public File_nameContext file_name() {
			return GetRuleContext<File_nameContext>(0);
		}
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode REDIRECT_OUT() { return GetToken(JollyShellParser.REDIRECT_OUT, 0); }
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode APPEND_OUT() { return GetToken(JollyShellParser.APPEND_OUT, 0); }
		public Io_redirect_fileContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_io_redirect_file; } }
	}

	[RuleVersion(0)]
	public Io_redirect_fileContext io_redirect_file() {
		Io_redirect_fileContext _localctx = new Io_redirect_fileContext(Context, State);
		EnterRule(_localctx, 16, RULE_io_redirect_file);
		try {
			State = 99;
			ErrorHandler.Sync(this);
			switch (TokenStream.LA(1)) {
			case REDIRECT_IN:
				EnterOuterAlt(_localctx, 1);
				{
				State = 93;
				Match(REDIRECT_IN);
				State = 94;
				file_name();
				}
				break;
			case REDIRECT_OUT:
				EnterOuterAlt(_localctx, 2);
				{
				State = 95;
				Match(REDIRECT_OUT);
				State = 96;
				file_name();
				}
				break;
			case APPEND_OUT:
				EnterOuterAlt(_localctx, 3);
				{
				State = 97;
				Match(APPEND_OUT);
				State = 98;
				file_name();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class Io_here_docContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode HEREDOC() { return GetToken(JollyShellParser.HEREDOC, 0); }
		[System.Diagnostics.DebuggerNonUserCode] public Here_endContext here_end() {
			return GetRuleContext<Here_endContext>(0);
		}
		public Io_here_docContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_io_here_doc; } }
	}

	[RuleVersion(0)]
	public Io_here_docContext io_here_doc() {
		Io_here_docContext _localctx = new Io_here_docContext(Context, State);
		EnterRule(_localctx, 18, RULE_io_here_doc);
		try {
			EnterOuterAlt(_localctx, 1);
			{
			State = 101;
			Match(HEREDOC);
			State = 102;
			here_end();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class Here_endContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode WORD() { return GetToken(JollyShellParser.WORD, 0); }
		public Here_endContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_here_end; } }
	}

	[RuleVersion(0)]
	public Here_endContext here_end() {
		Here_endContext _localctx = new Here_endContext(Context, State);
		EnterRule(_localctx, 20, RULE_here_end);
		try {
			EnterOuterAlt(_localctx, 1);
			{
			State = 104;
			Match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class File_nameContext : ParserRuleContext {
		[System.Diagnostics.DebuggerNonUserCode] public ITerminalNode WORD() { return GetToken(JollyShellParser.WORD, 0); }
		public File_nameContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_file_name; } }
	}

	[RuleVersion(0)]
	public File_nameContext file_name() {
		File_nameContext _localctx = new File_nameContext(Context, State);
		EnterRule(_localctx, 22, RULE_file_name);
		try {
			EnterOuterAlt(_localctx, 1);
			{
			State = 106;
			Match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public override bool Sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 1: return pipeline_sempred((PipelineContext)_localctx, predIndex);
		case 5: return cmd_prefix_sempred((Cmd_prefixContext)_localctx, predIndex);
		case 6: return cmd_suffix_sempred((Cmd_suffixContext)_localctx, predIndex);
		}
		return true;
	}
	private bool pipeline_sempred(PipelineContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0: return Precpred(Context, 1);
		}
		return true;
	}
	private bool cmd_prefix_sempred(Cmd_prefixContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1: return Precpred(Context, 3);
		case 2: return Precpred(Context, 1);
		}
		return true;
	}
	private bool cmd_suffix_sempred(Cmd_suffixContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3: return Precpred(Context, 3);
		case 4: return Precpred(Context, 1);
		}
		return true;
	}

	private static int[] _serializedATN = {
		4,1,10,109,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
		7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,1,0,1,0,3,0,27,8,0,1,1,1,1,1,1,
		1,1,1,1,1,1,5,1,35,8,1,10,1,12,1,38,9,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
		2,1,2,1,2,1,2,1,2,3,2,52,8,2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,3,5,61,8,5,1,
		5,1,5,1,5,1,5,5,5,67,8,5,10,5,12,5,70,9,5,1,6,1,6,1,6,3,6,75,8,6,1,6,1,
		6,1,6,1,6,5,6,81,8,6,10,6,12,6,84,9,6,1,7,1,7,1,7,1,7,1,7,1,7,3,7,92,8,
		7,1,8,1,8,1,8,1,8,1,8,1,8,3,8,100,8,8,1,9,1,9,1,9,1,10,1,10,1,11,1,11,
		1,11,0,3,2,10,12,12,0,2,4,6,8,10,12,14,16,18,20,22,0,0,113,0,26,1,0,0,
		0,2,28,1,0,0,0,4,51,1,0,0,0,6,53,1,0,0,0,8,55,1,0,0,0,10,60,1,0,0,0,12,
		74,1,0,0,0,14,91,1,0,0,0,16,99,1,0,0,0,18,101,1,0,0,0,20,104,1,0,0,0,22,
		106,1,0,0,0,24,27,3,2,1,0,25,27,5,10,0,0,26,24,1,0,0,0,26,25,1,0,0,0,27,
		1,1,0,0,0,28,29,6,1,-1,0,29,30,3,4,2,0,30,36,1,0,0,0,31,32,10,1,0,0,32,
		33,5,5,0,0,33,35,3,4,2,0,34,31,1,0,0,0,35,38,1,0,0,0,36,34,1,0,0,0,36,
		37,1,0,0,0,37,3,1,0,0,0,38,36,1,0,0,0,39,40,3,10,5,0,40,41,3,8,4,0,41,
		42,3,12,6,0,42,52,1,0,0,0,43,44,3,10,5,0,44,45,3,8,4,0,45,52,1,0,0,0,46,
		52,3,10,5,0,47,48,3,6,3,0,48,49,3,12,6,0,49,52,1,0,0,0,50,52,3,6,3,0,51,
		39,1,0,0,0,51,43,1,0,0,0,51,46,1,0,0,0,51,47,1,0,0,0,51,50,1,0,0,0,52,
		5,1,0,0,0,53,54,5,1,0,0,54,7,1,0,0,0,55,56,5,1,0,0,56,9,1,0,0,0,57,58,
		6,5,-1,0,58,61,3,14,7,0,59,61,5,3,0,0,60,57,1,0,0,0,60,59,1,0,0,0,61,68,
		1,0,0,0,62,63,10,3,0,0,63,67,3,14,7,0,64,65,10,1,0,0,65,67,5,3,0,0,66,
		62,1,0,0,0,66,64,1,0,0,0,67,70,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,
		11,1,0,0,0,70,68,1,0,0,0,71,72,6,6,-1,0,72,75,3,14,7,0,73,75,5,1,0,0,74,
		71,1,0,0,0,74,73,1,0,0,0,75,82,1,0,0,0,76,77,10,3,0,0,77,81,3,14,7,0,78,
		79,10,1,0,0,79,81,5,1,0,0,80,76,1,0,0,0,80,78,1,0,0,0,81,84,1,0,0,0,82,
		80,1,0,0,0,82,83,1,0,0,0,83,13,1,0,0,0,84,82,1,0,0,0,85,92,3,16,8,0,86,
		87,5,4,0,0,87,92,3,16,8,0,88,89,5,4,0,0,89,92,3,18,9,0,90,92,3,18,9,0,
		91,85,1,0,0,0,91,86,1,0,0,0,91,88,1,0,0,0,91,90,1,0,0,0,92,15,1,0,0,0,
		93,94,5,6,0,0,94,100,3,22,11,0,95,96,5,7,0,0,96,100,3,22,11,0,97,98,5,
		9,0,0,98,100,3,22,11,0,99,93,1,0,0,0,99,95,1,0,0,0,99,97,1,0,0,0,100,17,
		1,0,0,0,101,102,5,8,0,0,102,103,3,20,10,0,103,19,1,0,0,0,104,105,5,1,0,
		0,105,21,1,0,0,0,106,107,5,1,0,0,107,23,1,0,0,0,11,26,36,51,60,66,68,74,
		80,82,91,99
	};

	public static readonly ATN _ATN =
		new ATNDeserializer().Deserialize(_serializedATN);


}
