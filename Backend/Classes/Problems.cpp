/*
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="../../favicon.ico">

<title>问题 7125 --翻倍</title>
<!-- 新 Bootstrap 核心 CSS 文件 -->
<link rel="stylesheet" href="template/bs3/bootstrap.min.css">

<!-- 可选的Bootstrap主题文件（一般不用引入） -->
<link rel="stylesheet" href="template/bs3/bootstrap-theme.min.css">
<link rel="stylesheet" href="template/bs3/white.css">
<link rel="stylesheet" href="template/bs3/katex.min.css">
<link rel="stylesheet" href="template/bs3/mathjax.css">
<link rel="stylesheet" href="template/bs3/semantic.min.css">
    <link rel='stylesheet' href='template/bs3/problem.css'>    <link href='/static/prettify/r298/prettify.css' rel='stylesheet'>
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="http://cdn.bootcss.com/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="http://cdn.bootcss.com/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body>

    <div class="container">
          <!-- Static navbar -->
      <nav class="navbar navbar-default" role="navigation" >
        <div class="container-fluid">
          <div class="navbar-header">
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
              <span class="sr-only">Toggle navigation</span>
              <span class="icon-bar"></span>
              <span class="icon-bar"></span>
              <span class="icon-bar"></span>
            </button>
            <a class="navbar-brand" href="./">小明的OJ</a>
          </div>
          <div id="navbar" class="navbar-collapse collapse">
            <ul class="nav navbar-nav">
                        <li ><a href="index.php">首页</a></li>
              <li ><a href="problemset.php">问题</a></li>
              <li ><a href="status.php">状态</a></li>
              <li ><a href="contest.php">竞赛&作业</a></li>
        <li ><a href="downloads.php">下载</a></li>
              <!--<li class="dropdown">
                <a href="#" class="dropdown-toggle" data-toggle="dropdown">Dropdown <span class="caret"></span></a>
                <ul class="dropdown-menu" role="menu">
                  <li><a href="#">Action</a></li>
                  <li><a href="#">Another action</a></li>
                  <li><a href="#">Something else here</a></li>
                  <li class="divider"></li>
                  <li class="dropdown-header">Nav header</li>
                  <li><a href="#">Separated link</a></li>
                  <li><a href="#">One more separated link</a></li>
                </ul>
              </li>
    -->
              <li ><a href="open_contest.php">月赛</a></li>
            </ul>
        <ul class="nav navbar-nav navbar-right">
        <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown"><span id="profile">Login</span><span class="caret"></span></a>
            <ul class="dropdown-menu" role="menu">
<script src="template/bs3/profile.php?1397263917" ></script>
              <!--<li><a href="../navbar-fixed-top/">Fixed top</a></li>-->
        </ul>
        </li>
            </ul>
          </div><!--/.nav-collapse -->
        </div><!--/.container-fluid -->
      </nav>



      <!-- Main component for a primary marketing message or call to action -->
      <div class="jumbotron">
<center><h2 class='lang_cn'>7125: 翻倍</h2><h2 class='lang_en hidden'>7125: </h2><h3><span class=green>输入文件: </span>double.in&nbsp;&nbsp;&nbsp;<span class=green>输出文件: </span>double.out&nbsp;&nbsp;&nbsp;</h3><span class=green>时间限制: </span>1 Sec&nbsp;&nbsp;<span class=green>内存限制: </span>256 MB<br><span class=green>提交: </span>421&nbsp;&nbsp;<span class=green>解决: </span>195<br>[<a target='_blank' href='submitpage.php?id=7125'>提交</a>][<a href='problemstatus.php?id=7125'>状态</a>]</center><div class='cnt-row'><div class='cnt-row-head title'>题目描述</div><div class='cnt-row-body'><div class='content lang_cn'><p>
    小明喜欢吃饼干。他有一个神奇的机器，每次放进去一些饼干，然后启动一次机器，就会得到 $2$ 倍的饼干。
</p>
<p>
    今天，小明想吃 $N$ 块饼干，不能多吃也不能少吃。他一开始有 $1$ 块饼干，需要通过启动机器来获得 $N$ 块饼干。
</p>
<p>
    问，他最少需要启动多少次机器。
</p></div><div class='content lang_en hidden'></div></div></div><div class='cnt-row'><div class='cnt-row-head title'>输入</div><div class='cnt-row-body'><div class='content lang_cn'><p>
    一个整数 $N$。
</p></div><div class='content lang_en hidden'></div></div></div><div class='cnt-row'><div class='cnt-row-head title'>输出</div><div class='cnt-row-body'><div class='content lang_cn'><p>
    一个整数，表示小明最少需要启动多少次机器。
</p></div><div class='content lang_en hidden'></div></div></div><div class='cnt-row'><div class='cnt-row-head title'>样例输入输出</div><div class='cnt-row-body'><div class='data-sample'><div class='in-out'><div class='in-out-item' style='margin-right:.5em;'><span class='title'>样例输入 #1</span><a class='copy-btn'>复制</a><pre class='content' style='overflow:auto;'><span class=sampledata>3
</span></pre></div><div class='in-out-item' style='margin-left:.5em;'><span class='title'>样例输出 #1</span><a class='copy-btn'>复制</a><pre class='content' style='overflow:auto;'><span class=sampledata>2
</span></pre></div></div><div style='margin:.5em 0;'><div class='title' style='margin:.8em 0;'>样例说明 #1</div><div class='content lang_cn'><p>
    放入 $1$ 块饼干，启动一次机器，得到 $2$ 块饼干。
</p>
<p>
    再放入&nbsp;$1$ 块饼干，启动一次机器，得到 $2$ 块饼干。
</p>
<p>
    总计得到 $3$ 块饼干，启动了 $2$ 次机器。
</p></div><div class='content lang_en hidden'></div></div></div><div class='data-sample'><div class='in-out'><div class='in-out-item' style='margin-right:.5em;'><span class='title'>样例输入 #2</span><a class='copy-btn'>复制</a><pre class='content' style='overflow:auto;'><span class=sampledata>4
</span></pre></div><div class='in-out-item' style='margin-left:.5em;'><span class='title'>样例输出 #2</span><a class='copy-btn'>复制</a><pre class='content' style='overflow:auto;'><span class=sampledata>2
</span></pre></div></div><div style='margin:.5em 0;'><div class='title' style='margin:.8em 0;'>样例说明 #2</div><div class='content lang_cn'><p>
    放入 $1$ 块饼干，启动一次机器，得到 $2$ 块饼干。
</p>
<p>
    再放入 $2$ 块饼干，启动一次机器，得到 $4$ 块饼干。
</p>
<p>
    总计得到 $4$ 块饼干，启动了 $2$ 次机器。
</p></div><div class='content lang_en hidden'></div></div></div><div class='data-sample'><div class='in-out'><div class='in-out-item' style='margin-right:.5em;'><span class='title'>样例输入 #3</span><a class='copy-btn'>复制</a><pre class='content' style='overflow:auto;'><span class=sampledata>1000
</span></pre></div><div class='in-out-item' style='margin-left:.5em;'><span class='title'>样例输出 #3</span><a class='copy-btn'>复制</a><pre class='content' style='overflow:auto;'><span class=sampledata>10
</span></pre></div></div></div></div><div class='cnt-row'><div class='cnt-row-head title'>数据范围</div><div class='cnt-row-body'><div class='content lang_cn'><p>
    $1 \le N \le 10^8$
</p></div><div class='content lang_en hidden'></div></div><center>[<a target='_blank' href='submitpage.php?id=7125'>提交</a>][<a href='problemstatus.php?id=7125'>状态</a>]</center>      </div>
    </div> <!-- /container -->


    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <!-- jQuery文件。务必在bootstrap.min.js 之前引入 -->
<script src="template/bs3/jquery.min.js"></script>

<!-- 最新的 Bootstrap 核心 JavaScript 文件 -->
<script src="template/bs3/bootstrap.min.js"></script>

<!--<script type="text/javascript"
  src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML">
</script>
-->
<script>
$(document).ready(function(){
  var msg="<marquee style='margin-top:10px' id=broadcast scrollamount=1 scrolldelay=50 onMouseOver='this.stop()'"+
      " onMouseOut='this.start()' class=toprow>"+"\u5feb\u4e50\u5b66\u4e60\uff0c\u8ba4\u771f\u5237\u9898\uff0c\u52aa\u529b\u8fdb\u6b65\uff01\r\n"+"</marquee>";
  $(".jumbotron").prepend(msg);
  $("form").append("<div id='csrf' />");
  $("#csrf").load("csrf.php");
});


</script>


<script>
function phpfm(pid){
        //alert(pid);
        $.post("admin/phpfm.php",{'frame':3,'pid':pid,'pass':''},function(data,status){
                if(status=="success"){
                        document.location.href="admin/phpfm.php?frame=3&pid="+pid;
                }
        });
}
$(function() {
    $('.copy-btn').click(function() {
        const span = $(this).next().find('.sampledata');
        if (!span.length) {
            console.log('未找到pre');
            return;
        }
        const textarea = $('<textarea></textarea>').attr('readonly', 'readonly').text(span.text());
        console.log(textarea.text());
        document.body.appendChild(textarea[0]);
        // textarea.setSelectionRange(0, textarea.text().length);
        textarea.select();
        if (document.execCommand('copy')) {
            console.log('复制成功: ', textarea.text());
            $(this).text('复制成功').addClass('done');
            setTimeout("$('.copy-btn').text('复制').removeClass('done');", 1000);
        }
        document.body.removeChild(textarea[0]);
    });
    $("#lang_cn_to_en").click(function() {
        $("#lang_cn_to_en,.lang_cn").addClass("hidden");
        $("#lang_en_to_cn,.lang_en").removeClass("hidden");
    });
    $("#lang_en_to_cn").click(function() {
        $("#lang_cn_to_en,.lang_cn").removeClass("hidden");
        $("#lang_en_to_cn,.lang_en").addClass("hidden");
    });
    prettyPrint();
});
</script>
<script type="text/javascript" defer src="/mathjax/mathjax-config.js"></script>
<script type="text/javascript" defer id="MathJax-script" src="/mathjax/tex-chtml.js"></script>
<script type="text/javascript" src='/static/prettify/r298/prettify.js'></script>
</body>
</html>
<!--not cached-->


 */

#include "Problems.hpp"
#include <Database.hpp>
#include <Utilities/WebRequest.hpp>
#include <htmlparser/html.hpp>
#include <Classes/Settings.hpp>

PROBLEM PROBLEMS::Get(int ID, bool NoCache)
{
    DATABASE::SQL_DATA SQLData = Database.Select("Problems", {}, {{"ID", std::to_string(ID)}});
    bool HaveCache = SQLData.Data.size();
    PROBLEM Problem;
    if (!HaveCache || NoCache)
    {
        if (HaveCache)
            Database.Delete("Problems", {{"ID", std::to_string(ID)}});
        std::string HTMLData = WEB_REQUEST().Get(SETTINGS::Get("XMOJBaseURL") + "/problem.php?id=" + std::to_string(ID))->Send()->AssertResponseCode(200)->GetResponseBody();
        html::parser HTMLParser;
        html::node_ptr Node = HTMLParser.parse(HTMLData);
        Problem.Name = Node->select("h2.lang_cn")[0]->to_text();
        Problem.InputFilename = Node->select("span.green:contains(输入文件:)")[0]->get_parent()->at(1)->to_text();
        Problem.OutputFilename = Node->select("span.green:contains(输出文件:)")[0]->get_parent()->at(1)->to_text();
        Problem.TimeLimit = ASSERT_DIFFERENT(std::stoi(Node->select("span.green:contains(时间限制:)")[0]->get_parent()->at(1)->to_text()), 0);
        Problem.MemoryLimit = ASSERT_DIFFERENT(std::stoi(Node->select("span.green:contains(内存限制:)")[0]->get_parent()->at(1)->to_text()), 0);
        Problem.SpecialJudge = Node->select("span.red:contains(Special Judge)").size();
        Problem.EnableO2 = Node->select("span.green:contains(编译参数: -O2)").size();
        Problem.SubmitCount = ASSERT_DIFFERENT(std::stoi(Node->select("span.green:contains(提交:)")[0]->get_parent()->at(1)->to_text()), 0);
        Problem.SolvedCount = ASSERT_DIFFERENT(std::stoi(Node->select("span.green:contains(解决:)")[0]->get_parent()->at(1)->to_text()), 0);
    }
    else
    {
        // TODO
    }
    return Problem;
}