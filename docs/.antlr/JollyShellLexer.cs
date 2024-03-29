//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     ANTLR Version: 4.13.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from /mnt/nfs/homes/lannur-s/42/42MiniShell/docs/JollyShellLexer.g4 by ANTLR 4.13.1

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
using Antlr4.Runtime;
using Antlr4.Runtime.Atn;
using Antlr4.Runtime.Misc;
using DFA = Antlr4.Runtime.Dfa.DFA;

[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.13.1")]
[System.CLSCompliant(false)]
public partial class JollyShellLexer : Lexer {
	protected static DFA[] decisionToDFA;
	protected static PredictionContextCache sharedContextCache = new PredictionContextCache();
	public const int
		WORD=1, NAME=2, ASSIGNMENT_WORD=3, IO_NUMBER=4, PIPE=5, REDIRECT_IN=6, 
		REDIRECT_OUT=7, HEREDOC=8, APPEND_OUT=9, LINEBREAK=10;
	public static string[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static string[] modeNames = {
		"DEFAULT_MODE"
	};

	public static readonly string[] ruleNames = {
		"WORD", "NAME", "ASSIGNMENT_WORD", "IO_NUMBER", "PIPE", "REDIRECT_IN", 
		"REDIRECT_OUT", "HEREDOC", "APPEND_OUT", "LINEBREAK"
	};


	public JollyShellLexer(ICharStream input)
	: this(input, Console.Out, Console.Error) { }

	public JollyShellLexer(ICharStream input, TextWriter output, TextWriter errorOutput)
	: base(input, output, errorOutput)
	{
		Interpreter = new LexerATNSimulator(this, _ATN, decisionToDFA, sharedContextCache);
	}

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

	public override string GrammarFileName { get { return "JollyShellLexer.g4"; } }

	public override string[] RuleNames { get { return ruleNames; } }

	public override string[] ChannelNames { get { return channelNames; } }

	public override string[] ModeNames { get { return modeNames; } }

	public override int[] SerializedAtn { get { return _serializedATN; } }

	static JollyShellLexer() {
		decisionToDFA = new DFA[_ATN.NumberOfDecisions];
		for (int i = 0; i < _ATN.NumberOfDecisions; i++) {
			decisionToDFA[i] = new DFA(_ATN.GetDecisionState(i), i);
		}
	}
	private static int[] _serializedATN = {
		4,0,10,57,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,
		2,7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,5,0,24,8,0,10,0,12,0,27,9,0,1,1,1,1,5,
		1,31,8,1,10,1,12,1,34,9,1,1,2,1,2,1,2,1,3,4,3,40,8,3,11,3,12,3,41,1,4,
		1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,8,1,9,1,9,0,0,10,1,1,3,2,5,3,
		7,4,9,5,11,6,13,7,15,8,17,9,19,10,1,0,5,3,0,45,57,65,90,97,122,5,0,45,
		45,47,57,65,90,95,95,97,122,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,
		95,97,122,1,0,48,57,59,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,
		0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,
		0,0,0,1,21,1,0,0,0,3,28,1,0,0,0,5,35,1,0,0,0,7,39,1,0,0,0,9,43,1,0,0,0,
		11,45,1,0,0,0,13,47,1,0,0,0,15,49,1,0,0,0,17,52,1,0,0,0,19,55,1,0,0,0,
		21,25,7,0,0,0,22,24,7,1,0,0,23,22,1,0,0,0,24,27,1,0,0,0,25,23,1,0,0,0,
		25,26,1,0,0,0,26,2,1,0,0,0,27,25,1,0,0,0,28,32,7,2,0,0,29,31,7,3,0,0,30,
		29,1,0,0,0,31,34,1,0,0,0,32,30,1,0,0,0,32,33,1,0,0,0,33,4,1,0,0,0,34,32,
		1,0,0,0,35,36,3,3,1,0,36,37,5,61,0,0,37,6,1,0,0,0,38,40,7,4,0,0,39,38,
		1,0,0,0,40,41,1,0,0,0,41,39,1,0,0,0,41,42,1,0,0,0,42,8,1,0,0,0,43,44,5,
		124,0,0,44,10,1,0,0,0,45,46,5,60,0,0,46,12,1,0,0,0,47,48,5,62,0,0,48,14,
		1,0,0,0,49,50,5,60,0,0,50,51,5,60,0,0,51,16,1,0,0,0,52,53,5,62,0,0,53,
		54,5,62,0,0,54,18,1,0,0,0,55,56,5,10,0,0,56,20,1,0,0,0,4,0,25,32,41,0
	};

	public static readonly ATN _ATN =
		new ATNDeserializer().Deserialize(_serializedATN);


}
