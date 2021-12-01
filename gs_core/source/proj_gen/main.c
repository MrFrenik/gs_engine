/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine : Project Generator
    * File: main.c
    * Github: https://github.com/MrFrenik/gs_engine

    All Rights Reserved

    BSD 3-Clause License

    Copyright (c) 2020 John Jackson

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
    endorse or promote products derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIEDi
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=================================================================================================================*/ 

#define GS_NO_HIJACK_MAIN
#define GS_IMPL
#include <gs/gs.h>

GS_API_DECL gs_token_t gs_lexer_gen_next_token(gs_lexer_t* lex)
{
	gs_token_t t = gs_token_invalid_token();
	t.text = lex->at;
	t.len = 1;

	if (lex->can_lex(lex)) 
    { 
		char c = *lex->at;
		switch (c)
		{
			case '(': {t.type = GS_TOKEN_LPAREN; lex->at++;} break;
			case ')': {t.type = GS_TOKEN_RPAREN; lex->at++;} break;
			case '<': {t.type = GS_TOKEN_LTHAN; lex->at++;} break;
			case '>': {t.type = GS_TOKEN_GTHAN; lex->at++;} break;
			case ';': {t.type = GS_TOKEN_SEMI_COLON; lex->at++;} break;
			case ':': {t.type = GS_TOKEN_COLON; lex->at++;} break;
			case ',': {t.type = GS_TOKEN_COMMA; lex->at++;} break;
			case '=': {t.type = GS_TOKEN_EQUAL; lex->at++;} break;
			case '!': {t.type = GS_TOKEN_NOT; lex->at++;} break;
			case '#': {t.type = GS_TOKEN_HASH; lex->at++;} break;
			case '|': {t.type = GS_TOKEN_PIPE; lex->at++;} break;
			case '&': {t.type = GS_TOKEN_AMPERSAND; lex->at++;} break;
			case '{': {t.type = GS_TOKEN_LBRACE; lex->at++;} break;
			case '}': {t.type = GS_TOKEN_RBRACE; lex->at++;} break;
			case '[': {t.type = GS_TOKEN_LBRACKET; lex->at++;} break;
			case ']': {t.type = GS_TOKEN_RBRACKET; lex->at++;} break;
			case '-': {t.type = GS_TOKEN_MINUS; lex->at++;} break;
			case '+': {t.type = GS_TOKEN_PLUS; lex->at++;} break;
			case '*': {t.type = GS_TOKEN_ASTERISK; lex->at++;} break;
			case '%': {t.type = GS_TOKEN_PERCENT; lex->at++;} break;
			case '\\': {t.type = GS_TOKEN_BSLASH; lex->at++;} break;
			case '?': {t.type = GS_TOKEN_QMARK; lex->at++;} break;
			case ' ': {t.type = GS_TOKEN_SPACE; lex->at++;} break;
			case '\n': {t.type = GS_TOKEN_NEWLINE; lex->at++;} break;
			case '\r': {t.type = GS_TOKEN_NEWLINE; lex->at++;} break;
			case '\t': {t.type = GS_TOKEN_TAB; lex->at++;} break; 
			case '/':  {t.type = GS_TOKEN_FSLASH; lex->at++;} break; 
			case '"':  {t.type = GS_TOKEN_DOUBLE_QUOTE; lex->at++;} break;
			
			// Alpha/Numeric/Identifier
			default: 
			{
				if ((gs_char_is_alpha(c) || c == '_') && c != '-')
				{
					while (
						gs_char_is_alpha(lex->at[0]) || 
						gs_char_is_numeric(lex->at[0]) || 
						lex->at[0] == '_'
					)
					{
						lex->at++;
					}

					t.len = lex->at - t.text;
					t.type = GS_TOKEN_IDENTIFIER;
				}
				else if (gs_char_is_numeric(c) || c == '-')
				{
					uint32_t num_decimals = 0;
					while (
						gs_char_is_numeric(lex->at[0]) || 
						(lex->at[0] == '.' && num_decimals == 0) || 
						lex->at[0] == 'f'
					)
					{
						// Grab decimal
						num_decimals = lex->at[0] == '.' ? num_decimals++ : num_decimals;

						//Increment
						lex->at++;
					}

					t.len = lex->at - t.text;
					t.type = GS_TOKEN_NUMBER;
				}
				else
				{
					t.type = GS_TOKEN_UNKNOWN;
					lex->at++;
				}

			} break;
		}
	}

	// Set current token for lex
	lex->current_token = t;

	return t;
}

GS_API_DECL gs_lexer_t gs_lexer_gen_ctor(const char* contents)
{
	gs_lexer_t lex = gs_default_val();
	lex.contents = contents;
	lex.at = contents;
	lex.can_lex = gs_lexer_c_can_lex;
	lex.eat_white_space = gs_lexer_c_eat_white_space;
	lex.next_token = gs_lexer_gen_next_token;
	return lex;
}

void output_template(const char* proj_name, const char* core_dir, const char* proj_dir, const char* template_path, const char* out_path)
{ 
    size_t len = 0;
    char* template = gs_platform_read_file_contents(template_path, "r", &len);
    gs_assert(template);

	// Open file for writing
	FILE* fp = fopen(out_path, "w");
	if (!fp) 
	{
		return;
	}

    // Lex through proc template, look for tags for replacement
	gs_lexer_t lex = gs_lexer_gen_ctor(template);
    while (lex.can_lex(&lex))
    {
        gs_token_t token = lex.next_token(&lex);
        switch (token.type)
        {
            default:
            {
                gs_fprintf(fp, "%.*s", token.len, token.text);
            } break;

            case GS_TOKEN_PERCENT:
            {
                // Peek at next token, if identifier, then keep going
                gs_token_t nt = gs_lexer_peek(&lex);
                if (gs_token_compare_type(&nt, GS_TOKEN_IDENTIFIER))
                {
                    token = lex.next_token(&lex);

                    if (gs_token_compare_text(&token, "CORE_DIR"))
                    {
                        gs_fprintf(fp, "%s", core_dir);
                        if (!gs_lexer_find_next_token_type(&lex, GS_TOKEN_PERCENT)) gs_assert(false);
                    }
                    else if (gs_token_compare_text(&token, "APP_NAME"))
                    {
                        gs_fprintf(fp, "%s", proj_name);
                        if (!gs_lexer_find_next_token_type(&lex, GS_TOKEN_PERCENT)) gs_assert(false);
                    } 
                    else if (gs_token_compare_text(&token, "END"))
                    {
                        goto end;
                    }
                    else
                    {
                        gs_fprintf(fp, "%%"); 
                        gs_fprintf(fp, "%.*s", token.len, token.text); 
                    } 
                }
                else
                {
                    gs_fprintf(fp, "%.*s", token.len, token.text); 
                }

            } break;
        }
    }

end:
    fclose(fp);
}

int32_t main(int32_t argc, char** argv)
{ 
    if (argc < 2)
    {
        gs_println("ERROR: Must provide following arguments: '-proj_name {proj}'");
        return 0;
    }

    const char* proj_name = NULL;

    if (gs_string_compare_equal(argv[1], "-proj_name"))
    { 
        proj_name = argv[2];
    }

    if (!proj_name) proj_name = "new_project";

    // Necessary directories
    gs_snprintfc(PROJ_DIR, 256, "../%s", proj_name);
    gs_snprintfc(SOURCE_DIR, 256, "../%s/source", proj_name);
    gs_snprintfc(PROC_DIR, 256, "../%s/proc", proj_name);
    gs_snprintfc(PROC_WIN_DIR, 256, "../%s/proc/win", proj_name);
    gs_snprintfc(ASSETS_DIR, 256, "../%s/assets", proj_name);
    gs_snprintfc(CORE_DIR, 256, "../../gs_core/");
    gs_snprintfc(REFL_DIR, 256, "../%s/source/reflection", proj_name);

    // Now have to create directory for project
    // If it already exists, return early  
    DIR* dir = opendir(PROJ_DIR);   
    if (dir)
    {
        gs_println("ERROR: Project %s already exists.", proj_name);
        return 0;
    }
    closedir(dir); 

    // Make necessary directories for project
    mkdir(PROJ_DIR, S_IWRITE | S_IREAD); 
    mkdir(SOURCE_DIR, S_IWRITE | S_IREAD);
    mkdir(ASSETS_DIR, S_IWRITE | S_IREAD); 
    mkdir(PROC_DIR, S_IWRITE | S_IREAD);
    mkdir(PROC_WIN_DIR, S_IWRITE | S_IREAD); 
    mkdir(REFL_DIR, S_IWRITE | S_IREAD);

    gs_transient_buffer(OUT_PATH, 256);

    gs_println("Output proc/win/cl.bat...");
    
    // win/proc template
    gs_snprintf(OUT_PATH, 256, "%s/cl.bat", PROC_WIN_DIR);
    output_template(proj_name, CORE_DIR, PROJ_DIR, "../gs_core/source/proj_gen/templates/cl.bat", OUT_PATH); 

    gs_println("Output %s.h...", proj_name);

    // App template
    gs_snprintf(OUT_PATH, 256, "%s/%s.h", SOURCE_DIR, proj_name);
    output_template(proj_name, CORE_DIR, PROJ_DIR, "../gs_core/source/proj_gen/templates/app.h", OUT_PATH, proj_name); 

    gs_println("Output %s_main.c...", proj_name);

    // App main
    gs_snprintf(OUT_PATH, 256, "%s/%s_main.c", SOURCE_DIR, proj_name);
    output_template(proj_name, CORE_DIR, PROJ_DIR, "../gs_core/source/proj_gen/templates/main.c", OUT_PATH, proj_name); 

    gs_println("Output %s_config.c...", proj_name);

    // App config
    gs_snprintf(OUT_PATH, 256, "%s/%s_config.c", SOURCE_DIR, proj_name);
    output_template(proj_name, CORE_DIR, PROJ_DIR, "../gs_core/source/proj_gen/templates/config.c", OUT_PATH); 

    return 0;
}
















