# Test generator for the Olympiad in Informatics

#### Objective

This project was built in order to help with the generation of test files for competitive programming contests, with the
pattern from the Romanian National Olympiad in Informatics in mind.

#### Contents

The project provides a [generator base class](generator.h) implementing logic for creating a batch of numbered tests
(input and ok files).

It also contains an example of a [customized generator](example_generator.h) for a simple problem (a+b).

The project is implemented following the C++14 standard.

#### Usage

Below you can find the steps for creating tests for a problem:
- fork this project on your GitHub account (or simply download it if you are not planning to use version control);
- create a derived class from [Generator](generator.h) for each problem (see an [example](example_generator.h));
- implement the `generateInput` method for creating an input file based on a configuration. You can parametrize the
  function through the second argument of the method (in the example, it contains an upper bound for the values). This
  method can be omitted if the input files already exist in the destination folder - in this case, make sure you set
  `generateInputFiles` to `false` in the constructor (the input files should still follow the naming convention). For
  random generation of various values and objects, the [Utils](utils.h) class is provided and instantiated as a member
  in the generator;
- implement the `solve` method for creating ok files for existing input files. Here you should basically put your
  official solution. The reading and writing is done through the streams passed as arguments. Don't worry about opening
  and closing the files, as the generator does this automatically based on the naming convention. This method can be
  omitted if the problem has multiple solutions and verification is done by a program, or if the solution is not
  available yet - in this case, set `generateOkFiles` to `false` in the constructor;
- if the naming convention for the test files is different from the default (0-name.in, 0-name.ok), you can override the
  `getInputFileName` and `getOutputFileName` methods;
- call the inherited `generate` function. Pass as argument a `vector` containing the configuration for each test
  (limits, constraints - this should help you with creating data sets for partial scoring). The tests will be numbered
  in the order you provided, starting from 0 (alternatively you can set `testIndexStart` to other value in the
  constructor).
