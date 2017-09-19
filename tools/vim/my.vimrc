set nu
set ignorecase
set splitright
"set smartindent
"set autoindent
"set softtabstop=4
"set sw=4 ts=8
"set sw=4 ts=8 softtabstop=8 nosmarttab expandtab
"set softtabstop=8 
"set smarttab
"set expandtab" Disable if writing LKM or want tab characters
"set expandtab sw=8" Used for liquidio sources
set cindent
set cino=:0
highlight Search ctermbg=3
set laststatus=2

" Removes trailing white spaces at end of line in .c files while doing a :w
autocmd FileType c, autocmd BufWritePre <buffer> %s/\s\+$//e

function TabsOrSpaces()
    " Determines whether to use spaces or tabs on the current buffer.
    if getfsize(bufname("%")) > 256000
        echo "File is very large, using the default tab settings"
        return
    endif

    let numTabs=len(filter(getbufline(bufname("%"), 1, 256000), 'v:val =~ "^\\t"'))
    let numSpaces=len(filter(getbufline(bufname("%"), 1, 256000), 'v:val =~ "^ "'))

    "echo "Tabs found, spaces found " numTabs numSpaces
    if numTabs > numSpaces
        setlocal noexpandtab
        setlocal shiftwidth=8
        setlocal tabstop=8
    endif
endfunction

function SpaceIndent()
    setlocal expandtab
    setlocal shiftwidth=4
    setlocal tabstop=4
endfunction

function TabIndent()
    setlocal noexpandtab
    setlocal shiftwidth=8
    setlocal tabstop=8
endfunction

" By default, use tabs indent.
" Display tabs as 4 spaces wide. When expandtab is set, use 4 spaces.
set noexpandtab
set shiftwidth=8
set tabstop=8

" Call the function after opening a buffer
" Lets follow Linux style plugin .vim/plugin/linuxsty.vim
"autocmd BufReadPost * call TabsOrSpaces()
"set statusline=%t       "tail of the filename
"set statusline+=[%{strlen(&fenc)?&fenc:'none'}, "file encoding
"set statusline+=%{&ff}] "file format
"set statusline+=%h      "help file flag
"set statusline+=%m      "modified flag
"set statusline+=%r      "read only flag
"set statusline+=%y      "filetype
"set statusline+=%=      "left/right separator
"set statusline+=%c,     "cursor column
"set statusline+=%l/%L   "cursor line/total lines
"set statusline+=\ %P    "percent through file
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" CSCOPE settings for vim           
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"
" This file contains some boilerplate settings for vim's cscope interface,
" plus some keyboard mappings that I've found useful.
"
" USAGE: 
" -- vim 6:     Stick this file in your ~/.vim/plugin directory (or in a
"               'plugin' directory in some other directory that is in your
"               'runtimepath'.
"
" -- vim 5:     Stick this file somewhere and 'source cscope.vim' it from
"               your ~/.vimrc file (or cut and paste it into your .vimrc).
"
" NOTE: 
" These key maps use multiple keystrokes (2 or 3 keys).  If you find that vim
" keeps timing you out before you can complete them, try changing your timeout
" settings, as explained below.
"
" Happy cscoping,
"
" Jason Duell       jduell@alumni.princeton.edu     2002/3/7
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

"set statusline
" This tests to see if vim was configured with the '--enable-cscope' option
" when it was compiled.  If it wasn't, time to recompile vim... 
if has("cscope")

    """"""""""""" Standard cscope/vim boilerplate

    " use both cscope and ctag for 'ctrl-]', ':ta', and 'vim -t'
    set cscopetag

    " check cscope for definition of a symbol before checking ctags: set to 1
    " if you want the reverse search order.
    set csto=0

    " add any cscope database in current directory or previous directories
    let cnt = 10
    let db = "cscope.out"
    let dbfile = "cscope.db.vim"
    if $CSCOPE_DB != ""
    " else add the database pointed to by environment variable 
    let db = $CSCOPE_DB
    endif
    while cnt > 0
	    if filereadable(db)
				echo "Adding Cscope of " db
				set nocscopeverbose
				exe "cscope add " . db
        
                " Add cscope file mentioned in db file
                if filereadable(dbfile)
                    let extra_db = ""
                    exec  "source " . dbfile
                    if filereadable(extra_db)
                                echo "Adding cscope of " extra_db
                                exec "cscope add " . extra_db
                    endif
                endif
				
				set cscopeverbose
                break
        endif
            
        let db = "../" . db
	    let dbfile = "../" . dbfile
		let cnt = cnt - 1
	endwhile


    " Add octeon root cscope if present
    set nocscopeverbose
    if $OCTEON_ROOT != ""
    	let db = $OCTEON_ROOT .  "/cscope.out"
    	if filereadable(db)
				echo "Adding cscope of " db
				exec "cscope add " . db
	    endif
    elseif $THUNDER_ROOT != ""
    	let db = $THUNDER_ROOT .  "/cscope.out"
    	if filereadable(db)
				echo "Adding cscope of " db
				exec "cscope add " . db
	    endif
    endif


    " show msg when any other cscope db added
    set cscopeverbose  


    """"""""""""" My cscope/vim key mappings
    "
    " The following maps all invoke one of the following cscope search types:
    "
    "   's'   symbol: find all references to the token under cursor
    "   'g'   global: find global definition(s) of the token under cursor
    "   'c'   calls:  find all calls to the function name under cursor
    "   't'   text:   find all instances of the text under cursor
    "   'e'   egrep:  egrep search for the word under cursor
    "   'f'   file:   open the filename under cursor
    "   'i'   includes: find files that include the filename under cursor
    "   'd'   called: find functions that function under cursor calls
    "
    " Below are three sets of the maps: one set that just jumps to your
    " search result, one that splits the existing vim window horizontally and
    " diplays your search result in the new window, and one that does the same
    " thing, but does a vertical split instead (vim 6 only).
    "
    " I've used CTRL-\ and CTRL-@ as the starting keys for these maps, as it's
    " unlikely that you need their default mappings (CTRL-\'s default use is
    " as part of CTRL-\ CTRL-N typemap, which basically just does the same
    " thing as hitting 'escape': CTRL-@ doesn't seem to have any default use).
    " If you don't like using 'CTRL-@' or CTRL-\, , you can change some or all
    " of these maps to use other keys.  One likely candidate is 'CTRL-_'
    " (which also maps to CTRL-/, which is easier to type).  By default it is
    " used to switch between Hebrew and English keyboard mode.
    "
    " All of the maps involving the <cfile> macro use '^<cfile>$': this is so
    " that searches over '#include <time.h>" return only references to
    " 'time.h', and not 'sys/time.h', etc. (by default cscope will return all
    " files that contain 'time.h' as part of their name).


    " To do the first type of search, hit 'CTRL-\', followed by one of the
    " cscope search types above (s,g,c,t,e,f,i,d).  The result of your cscope
    " search will be displayed in the current window.  You can use CTRL-T to
    " go back to where you were before the search.  
    "
nmap <silent> <F6><F6> :cs find e <cword><CR>
nmap <silent> <F7><F7> :cs find f <cfile><CR>
nmap <silent> <F8><F8> :cs find i <cfile><CR>
nmap <silent> <F9><F9> :cs find g <cword><CR>
nmap <silent> <C-@><F9><F9> :vert scs find g <C-R>=expand("<cword>")<CR><CR>
nmap <silent> <F10><F10> :cs find s <cword><CR>
nmap <silent> <F11><F11> :cs find c <cword><CR>
nmap <silent> <F12><F12> :cs find t <cword><CR><CR>
nmap <C-\>d :cs find d =expand("")

" Mapping for text based input
nmap <silent> <F6> :exe "cs find e " . Loadinput("Find this egrep pattern: ")<CR>
nmap <silent> <F7> :exe "cs find f " . Loadinput("Find this file: ")<CR>
nmap <silent> <F8> :exe "cs find i " . Loadinput("Find files #including this file: ")<CR>
nmap <silent> <F9> :exec "cs find g " . Loadinput("Find this global definition: ")<CR>
nmap <silent> <F10> :exec "cs find s " . Loadinput("Find this C symbol: ")<CR>
nmap <silent> <F11> :exec "cs find c " . Loadinput("Find functions calling this function: ")<CR>
nmap <silent> <F12> :exec "cs find t " . Loadinput("Find this text string: ")<CR>
function Loadinput(str)
        set cscopeverbose  
	call inputsave()
	let g:inp = input(a:str)
        call inputrestore()
        return g:inp
endfunction

"    nmap <F6> :cs find s =expand("")
"    nmap <F9> :cs find g <C-R>=expand("<cword>")<CR><CR>	
"    nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>	
"    nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>	
"    nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>	
"    nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>	
"    nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
"    nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>	


    " Using 'CTRL-spacebar' (intepreted as CTRL-@ by vim) then a search type
    " makes the vim window split horizontally, with search result displayed in
    " the new window.
    "
    " (Note: earlier versions of vim may not have the :scs command, but it
    " can be simulated roughly via:
    "    nmap <C-@>s <C-W><C-S> :cs find s <C-R>=expand("<cword>")<CR><CR>	

    nmap <C-@>s :scs find s <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>g :scs find g <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>c :scs find c <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>t :scs find t <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>e :scs find e <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>f :scs find f <C-R>=expand("<cfile>")<CR><CR>	
    nmap <C-@>i :scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>	
    nmap <C-@>d :scs find d <C-R>=expand("<cword>")<CR><CR>	


    " Hitting CTRL-space *twice* before the search type does a vertical 
    " split instead of a horizontal one (vim 6 and up only)
    "
    " (Note: you may wish to put a 'set splitright' in your .vimrc
    " if you prefer the new window on the right instead of the left

    nmap <C-@><C-@>s :vert scs find s <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>g :vert scs find g <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>c :vert scs find c <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>t :vert scs find t <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>e :vert scs find e <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>f :vert scs find f <C-R>=expand("<cfile>")<CR><CR>	
    nmap <C-@><C-@>i :vert scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>	
    nmap <C-@><C-@>d :vert scs find d <C-R>=expand("<cword>")<CR><CR>


    """"""""""""" key map timeouts
    "
    " By default Vim will only wait 1 second for each keystroke in a mapping.
    " You may find that too short with the above typemaps.  If so, you should
    " either turn off mapping timeouts via 'notimeout'.
    "
    "set notimeout 
    "
    " Or, you can keep timeouts, by uncommenting the timeoutlen line below,
    " with your own personal favorite value (in milliseconds):
    "
    "set timeoutlen=4000
    "
    " Either way, since mapping timeout settings by default also set the
    " timeouts for multicharacter 'keys codes' (like <F1>), you should also
    " set ttimeout and ttimeoutlen: otherwise, you will experience strange
    " delays as vim waits for a keystroke after you hit ESC (it will be
    " waiting to see if the ESC is actually part of a key code like <F1>).
    "
    "set ttimeout 
    "
    " personally, I find a tenth of a second to work well for key code
    " timeouts. If you experience problems and have a slow terminal or network
    " connection, set it higher.  If you don't set ttimeoutlen, the value for
    " timeoutlent (default: 1000 = 1 second, which is sluggish) is used.
    "
    "set ttimeoutlen=100

endif
if has("syntax")
    syntax on
endif

fu! Basename(filename)
            return fnamemodify(a:filename, ":t")
endfunction

" Make a proper C or H file template
fu! MakeCFile()
    set ft=c
    let oldfmt=&formatoptions
    set formatoptions=
    set modifiable
    let filename=Basename(bufname("%"))
    let date=strftime("%m/%d/%Y")
    let year=strftime("%Y")
    normal 1G
    normal i/*
    normal 75a-
    normal o
    normal 2i 
    normal i*
    normal o
    normal 2i 
    normal i*
    exec "normal a " . filename
    normal o*
    normal o*
    normal 75a-
    normal o*/
    normal o

    let h_file=0
    " if the last letter is H, do some special processing
    if ( strridx(filename,"h") == strlen(filename)-1 ) 
        echo "H file!!!"
        let h_file=1
    endif

    if ( h_file == 1 )
        let defname='__' . toupper(filename) . '__'
        let defname=substitute(defname,"\\.","_","g")
	let defname=substitute(defname,"\\-","_","g")

        exec "normal o#ifndef " . defname
        exec "normal o#define " . defname
        normal o
        exec "normal o#endif /* " . defname . " */"
    else
        " normal o#include "l2tp_inc.h"
        normal o
    endif
    exec "set formatoptions=" . oldfmt
endfunction

if has("autocmd")
"  autocmd Syntax c!
"  autocmd Syntax h!

    if (!exists("g:autocmds_installed"))
        let g:autocmds_installed = 1
        " echo "Setting autocmds for syntax "

        " just call MiscFiles() for everything....
        " autocmd Syntax help           call MiscFiles()
        " autocmd Syntax tcl            call MiscFiles()
        " autocmd Syntax vim            call MiscFiles()

        " autocmd BufEnter *            call MiscFiles() 
        " autocmd GUIEnter *            call SetColors()

        " autocmd Syntax c              call CSetup()
        " autocmd Syntax cpp            call CSetup()
        " autocmd Syntax h              call CSetup()

        " 2007/12/04 Tuesday - don't need to do this since we already
        " called MiscFiles at BufEnter time.
        " autocmd Syntax *              call MiscFiles()

        autocmd BufNewFile *.c,*.h    call MakeCFile()
        " autocmd BufEnter *.ddl        set ft=c
        " autocmd Syntax xdefaults      call MiscFiles()
        " autocmd BufNewFile commit_msg    call CvsMakeTemplate()
    endif

endif

if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$") | exe "normal! g`\"" | endif
  endif

" Open each buffer in new tab
" au BufAdd,BufNewFile * nested tab sball
map <C-N>   :bn<CR>
map <C-P>   :bp<CR>
nnoremap <C-r> :bdelete<cr>

" Open Tagbar 
nmap <F4>  :TagbarToggle<CR>

" Window movement mappings
nmap <C-h> <C-W>h
nmap <C-j> <C-W>j
nmap <C-k> <C-W>k
nmap <C-l> <C-W>l

fun! ShowFuncName()
  echohl ModeMsg
  echo getline(search("^[^ \t#/]\\{2}.*[^:]\s*$", 'bWn'))
  echohl None
endfun
map f :call ShowFuncName() <CR>

command! Z mksession! ~/.vim/mysession.vim | qall

